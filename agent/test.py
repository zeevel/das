import argparse
import random

import gym
import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from ns3gym import ns3env

parser = argparse.ArgumentParser(description="Start simulation script on/off")
parser.add_argument(
    "--start", type=int, default=0, help="Start simulation script 0/1, Default:0"
)
parser.add_argument(
    "--iterations", type=int, default=30, help="Number of iterations, Default: 1"
)

args = parser.parse_args()
startSim = bool(args.start)
iterationNum = int(args.iterations)

port = 5555
simTime = 50
stepTime = 0.1
seed = 1
simArgs = {"--simTime": simTime, "--testArg": 123, "--nodeNum": 5, "--distance": 500}
debug = False

env = ns3env.Ns3Env(
    port=port,
    stepTime=stepTime,
    startSim=startSim,
    simSeed=seed,
    simArgs=simArgs,
    debug=debug,
)
env.reset()

ob_space = env.observation_space
ac_space = env.action_space
print("Observation space: ", ob_space, ob_space.dtype)
print("Action space: ", ac_space, ac_space.dtype)
print("状态: ", ob_space, type(ob_space))
print("动作: ", ac_space, type(ac_space))
print("动作空间: ", ac_space.n)

np.random.seed(1)

# 超参数
BATCH_SIZE = 256  # 批处理大小
LR = 0.01  # 学习率
EPSILON = 0.9  # 贪婪度
GAMMA = 0.9  # 衰减因子
TARGET_REPLACE_ITER = 100  # 多少步更新一次target_net模型
MEMORY_CAPACITY = 200  # 用于记录经验的缓存大小

N_ACTIONS = env.action_space.n
N_STATES = len(list(env.observation_space))

# print("N_STATIES: ", env.observation_space)
# print(list(env.observation_space))


print("N_ACTIONS: ", N_ACTIONS)
print("N_STATES: ", N_STATES)


def trans_to_tensor(data):
    val = [i for i in data.values()]
    return torch.Tensor(val)


def dict2array(dictData):
    valueList = list(dictData.values())
    return np.asarray(valueList)


class Net(nn.Module):
    def __init__(self):
        super(Net, self).__init__()
        self.fc1 = nn.Linear(N_STATES, 50)
        self.fc1.weight.data.normal_(0, 0.1)

        self.out = nn.Linear(50, N_ACTIONS)
        self.out.weight.data.normal_(0, 0.1)

    def forward(self, x):
        x = self.fc1(x)
        x = F.relu(x)
        actions_value = self.out(x)
        return actions_value


class DQN(object):
    def __init__(self):
        self.eval_net, self.target_net = Net(), Net()

        self.learn_step_counter = 0  # 用于target更新及时
        self.memory_counter = 0  # 记忆库计数
        self.memory = np.zeros((MEMORY_CAPACITY, N_STATES * 2 + 2))

        self.optimizer = torch.optim.Adam(self.eval_net.parameters(), lr=LR)
        self.loss_func = nn.MSELoss()
        self.cost_his = []
        self.reward_his = []

    def choose_action(self, x):
        # print("[DQN::choose_action], x: ", x, ", type is: ", type(x))
        # x = trans_to_tensor(x)
        # print("x and x's type: ", x, type(x))
        # x只是一个样本 给它添加一维
        x = torch.unsqueeze(torch.FloatTensor(x), 0)
        # input only one sample
        if np.random.uniform() < EPSILON:  # greedy
            actions_value = self.eval_net.forward(x)
            action = torch.max(actions_value, 1)[1].data.numpy()
            action = action[0]  # 取最大Q值对应的索引(即动作)
        else:
            action = np.random.randint(0, N_ACTIONS)
        return action

    def store_transition(self, s, a, r, s_):
        transition = np.hstack((s, [a, r], s_))
        index = self.memory_counter % MEMORY_CAPACITY
        # print("memory, transition: ", self.memory, transition)
        self.memory[index, :] = transition
        self.memory_counter += 1

    #  model update
    def learn(self):
        if self.learn_step_counter % TARGET_REPLACE_ITER == 0:
            self.target_net.load_state_dict(self.eval_net.state_dict())
            # torch.save(
            #     self.target_net.state_dict(), "model/effectStaTh-reward-model-2.pk1"
            # )
        self.learn_step_counter += 1

        # sample batch transition
        sample_index = np.random.choice(MEMORY_CAPACITY, BATCH_SIZE)
        b_memory = self.memory[sample_index, :]
        b_s = torch.FloatTensor(b_memory[:, :N_STATES])
        b_a = torch.LongTensor(b_memory[:, N_STATES : N_STATES + 1].astype(int))
        b_r = torch.FloatTensor(b_memory[:, N_STATES + 1 : N_STATES + 2])
        b_s_ = torch.FloatTensor(b_memory[:, -N_STATES:])

        # DDQN model update
        # Q_predict size: (BatchSize, 1); 历史记录中在s执行a这一行为 在 当前的eval_net网络中能获得到多少Q值
        q_eval = self.eval_net(b_s).gather(1, b_a)
        # 下一步s_输入实时网络eval_net， 提取出Q值最大的列index   shape=(BatchSize, 1)
        # (BatchSize, N_ACTIONS) ---max(dim=1)---> (BatchSize, 1)
        q_eval4next = self.eval_net(b_s_).max(1)[1].view(BATCH_SIZE, 1)
        # 下一步s_输入静态网络eval_target  shape=(BatchSize, N_ACTIONS)
        q_next = self.target_net(b_s_).detach()  # 反向传播时候不应该考虑这一步正向计算
        # 根据上述变量计算q_target shape=(BatchSize, 1)
        q_target = b_r + GAMMA * q_next.gather(1, q_eval4next)

        loss = self.loss_func(q_eval, q_target)

        if self.learn_step_counter % 10 == 0:
            self.cost_his.append(loss)

        self.optimizer.zero_grad()
        loss.backward()

    def plot_cost(self, episodeRewards):
        import matplotlib.pyplot as plt

        # recordHistory(
        #     "/home/zeevel/ndnSIM/ns-3/scratch/ndn-wireless-multicast/log/cost.txt",
        #     self.cost_his,
        # )
        # recordHistory(
        #     "/home/zeevel/ndnSIM/ns-3/scratch/ndn-wireless-multicast/log/reward.txt",
        #     self.reward_his,
        # )
        # recordHistory(
        #     "/home/zeevel/ndnSIM/ns-3/scratch/ndn-wireless-multicast/log/episodeRewards.txt",
        #     episodeRewards,
        # )

        plt.figure

        plt.subplot(311)
        plt.plot(np.arange(len(self.cost_his)), self.cost_his)
        plt.ylabel("Cost")
        plt.xlabel("training steps")
        plt.title("Cost History")
        # plt.show()

        plt.subplot(312)
        plt.plot(np.arange(len(self.reward_his)), self.reward_his)
        plt.ylabel("Reward")
        plt.xlabel("training steps")
        plt.title("Reward History")

        plt.subplot(313)
        plt.plot(np.arange(len(episodeRewards)), episodeRewards)
        plt.ylabel("episode total reward")
        plt.xlabel("episode number")
        plt.title("Reward History")

        plt.show()


def train():
    dqn = DQN()
    # dqn.eval_net.load_state_dict(torch.load(
    #     "/home/zeevel/dxj/ndnSIM2.6/ns-3/scratch/ndn-wireless-multicast/model/effectStaTh-reward-model-1.pk1"))
    # dqn.target_net.load_state_dict(torch.load(
    #     "/home/zeevel/dxj/ndnSIM2.6/ns-3/scratch/ndn-wireless-multicast/model/effectStaTh-reward-model-1.pk1"))
    currIt = 1
    stepIdx = 0
    try:
        s = env.reset()
        s = dict2array(s)
        print(
            "initial state is : ", s, " type is: ", type(s), "shape is: ", np.shape(s)
        )

        r = 0
        episodeRewards = []
        while True:
            print("========开始第", currIt, "回合\n")

            ep_r = 0

            print("Step: ", 0)
            print("---obs: ", s)

            for i in range(500):
                # rl agent choose action
                a = dqn.choose_action(s)
                print("---action: ", a)

                # ns3 environment take action a
                s_, r, done, info = env.step(a)
                print("env.step(a) 's response is: ", s_, r, done, info)
                # s_ = dict2list(s_)
                if s_ is None:  # first several step can be none
                    s_ = s
                else:
                    s_ = dict2array(s_)
                print("next state: ", s_)

                # store this transition
                dqn.store_transition(s, a, r, s_)

                # 更新本轮总奖励
                ep_r += r

                if dqn.memory_counter % 10 == 0:
                    dqn.reward_his.append(r)

                if dqn.memory_counter > MEMORY_CAPACITY:
                    print("更新模型参数DQN model update!!!!!!")
                    dqn.learn()
                    if done:
                        print("Ep: ", currIt, "| Ep_r: ", round(ep_r, 2))

                if done:
                    break

                s = s_
                print("Step: ", i + 1)
                print("---obs, reward, done, info: ", s, r, done, info)

            episodeRewards.append(ep_r)
            currIt += 1
            if currIt == iterationNum:
                break
        # dqn.plot_cost(episodeRewards)
    except KeyboardInterrupt:
        print("Ctrl-C -> Exit")
    finally:
        env.close()
        print("Done")


def test():
    currIt = 1
    # stepIdx = 0

    def get_action_from_model(obs):
        return random.randint(0, 3)

    # obs = np.asarray([1.0, 0.5, 0.5, 0.0, 0.0, 0.0, 1.0])
    # print(obs, obs.shape, type(obs))

    # print(get_action_from_model(obs))
    try:
        s = env.reset()
        print("type(obs) is: ", type(s))
        r = 0
        while True:
            print("========开始第", currIt, "回合\n")

            # ep_r = 0

            print("Step: ", 0)
            print("---obs: ", s)

            for i in range(500):
                # rl agent choose action
                a = get_action_from_model(s)
                print("---action: ", a, ", type: ", type(a))

                # ns3 environment take action a
                s_, r, done, info = env.step(a)
                print("env.step(a) 's response is: ", s_, r, done, info)
                print("next state: ", s_)

                if done:
                    break

                s = s_
                print("Step: ", i + 1)
                print("---obs, reward, done, info: ", s, r, done, info)
            currIt += 1
            if currIt == iterationNum:
                break
    except KeyboardInterrupt:
        print("Ctrl-C -> Exit")
    finally:
        env.close()
        print("Done")


if __name__ == "__main__":
    train()
    # test()
