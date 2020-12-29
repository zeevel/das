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
# N_STATES = env.observation_space.shape[0]


print("N_ACTIONS: ", N_ACTIONS)
# print("N_STATES: ", N_STATES)


def test():
    currIt = 1
    # stepIdx = 0

    def get_action_from_model(obs):
        return random.randint(0, 2)

    # obs = np.asarray([1.0, 0.5, 0.5, 0.0, 0.0, 0.0, 1.0])
    # print(obs, obs.shape, type(obs))

    # print(get_action_from_model(obs))
    try:
        s = env.reset()
        r = 0
        while True:
            print("========开始第", currIt, "回合\n")

            # ep_r = 0

            print("Step: ", 0)
            print("---obs: ", s)

            for i in range(500):
                # rl agent choose action
                a = get_action_from_model(s)
                print("---action: ", a)

                # ns3 environment take action a
                s_, r, done, info = env.step(a)

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
    # train()
    test()
