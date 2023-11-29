import urx
import numpy as np
import time
from   pyfirmata import Arduino

def deg2rad(deg):
    return deg*np.pi/180

def rad2deg(rad):
    return rad*180/np.pi

def home(robot):
    robot.movej((deg2rad(-90.00), deg2rad(-90), deg2rad(-90), deg2rad(-90), deg2rad(90), deg2rad(0)), 0.8, 0.80)

def getMarker(acc, vel, robot, relay_pin):
    robot.set_payload(1.100)
    unlockTool(relay_pin, 1)
    startPose = [deg2rad(-53.58), deg2rad(-121.79), deg2rad(-95.28), deg2rad(-52.73), deg2rad(91.37), deg2rad(37.63)]
    pose1 = [0.253, -0.6319, 0.006, 0.029, 3.118, -0.034]
    pose2 = [0.253, -0.6319, 0.313, 0.029, 3.118, -0.039]
    robot.movej((startPose), 0.8, 0.8)
    robot.movel((pose1), acc, vel)
    time.sleep(1)
    lockTool(relay_pin, 1)
    robot.movel((pose2), acc, vel)

def returnMarker(acc, vel, robot, relay_pin):
    startPose = [deg2rad(-53.58), deg2rad(-121.79), deg2rad(-95.28), deg2rad(-52.73), deg2rad(91.37), deg2rad(37.63)]
    pose1 = [0.253, -0.6319, 0.006, 0.029, 3.118, -0.034]
    pose2 = [0.253, -0.6319, 0.313, 0.029, 3.118, -0.039]
    robot.movej((startPose), 0.8, 0.8)
    robot.movel((pose1), acc, vel)
    time.sleep(1)
    unlockTool(relay_pin, 1)
    robot.set_payload(1.000)
    robot.movel((pose2), acc, vel)

def getGrinder(acc, vel, robot, relay_pin):
    robot.set_payload(2.600)
    unlockTool(relay_pin, 1)
    startPose = [deg2rad(-59.53), deg2rad(-137.03), deg2rad(-65.97), deg2rad(-66.12), deg2rad(89.43), deg2rad(30.07)]
    pose1 = [0.255, -0.7826, 0.003, 0.008, -3.138, -0.028]
    pose2 = [0.255, -0.7826, 0.252, 0.008, -3.138, -0.032]
    robot.movej((startPose), 0.8, 0.8)
    robot.movel((pose1), acc, vel)
    time.sleep(1)
    lockTool(relay_pin, 1)
    robot.movel((pose2), acc, vel)

def returnGrinder(acc, vel, robot, relay_pin):
    startPose = [deg2rad(-59.53), deg2rad(-137.03), deg2rad(-65.97), deg2rad(-66.12), deg2rad(89.43), deg2rad(30.07)]
    pose1 = [0.255, -0.7826, 0.003, 0.008, -3.138, -0.028]
    pose2 = [0.255, -0.7826, 0.252, 0.008, -3.138, -0.032]
    robot.movej((startPose), 0.8, 0.8)
    robot.movel((pose1), acc, vel)
    time.sleep(1)
    unlockTool(relay_pin, 1)
    robot.set_payload(1.000)
    robot.movel((pose2), acc, vel)


def cutPipe(acc, vel, robot):
    startPose = [0.003, -0.424, 0.232, 2.22, -2.221, 0.00]
    viaPose1  = [0.098, -0.587, 0.232, 2.98, -0.96, -0.00]
    endPose1  = [0.213, -0.636, 0.232, 3.13, -0.00, -0.00]
    viaPose2  = [0.362, -0.589, 0.232, 2.90,  1.18, -0.00]
    endPose2  = [0.435, -0.442, 0.232, 2.22,  2.21, -0.00]
    viaPose3  = [0.362, -0.589, 0.232, 2.90,  1.18, -0.00]
    endPose3  = [0.232, -0.638, 0.232, 3.13, -0.00, -0.00]
    viaPose4  = [0.099, -0.587, 0.232, 2.98, -0.96, -0.00]
    endPose4  = [0.003, -0.424, 0.232, 2.21, -2.22,  0.00]
    viaPose5  = [0.109, -0.260, 0.232, 1.0,  -2.97,  0.00]
    endPose5  = [0.237, -0.226, 0.232, 0,    -3.13,  0.00]
    viaPose6  = [0.356, -0.281, 0.232, 1.07,  2.95, -0.00]
    endPose6  = [0.424, -0.438, 0.232, 2.21,  2.23, -0.00]
    viaPose7  = [0.356, -0.281, 0.232, 1.07,  2.95, -0.00]
    endPose7  = [0.237, -0.226, 0.232, 0.00, -3.13,  0.00]
    viaPose8  = [0.109, -0.260, 0.232, 1.00, -2.97,  0.00]
    endPose8  = [0.003, -0.424, 0.232, 2.21, -2.22,  0.00]
    robot.movep((startPose), acc, vel)
    robot.movec((viaPose1) , (endPose1),acc,vel)
    robot.movec((viaPose2), (endPose2),acc,vel)
    robot.movec((viaPose3), (endPose3),acc,vel)
    robot.movec((viaPose4), (endPose4),acc,vel)
    robot.movec((viaPose5), (endPose5),acc,vel)
    robot.movec((viaPose6), (endPose6),acc,vel)
    robot.movec((viaPose7), (endPose7),acc,vel)
    robot.movec((viaPose8), (endPose8),acc,vel)

def drawD(acc, vel, robot):
    pose1    = [-0.134, -0.753, 0.2153,  2.211, -2.219, 0]
    pose2    = [-0.033, -0.753, 0.21625, 2.211, -2.219, 0]
    viaPose1 = [-0.067, -0.700, 0.21460, 2.211, -2.219, 0]
    endPose1 = [-0.134, -0.753, 0.2153,  2.211, -2.219, 0]
    pose3    = [-0.134, -0.751, 0.234,   2.211, -2.219, 0]
    robot.movels((pose1, pose2), acc, vel)
    robot.movec((viaPose1), (endPose1), acc, vel)
    robot.movel((pose3),vel,acc)

def drawO(acc, vel, robot):
    pose1    = [-0.134, -0.6357, 0.2159, 2.211, -2.219, 0]
    viaPose1 = [-0.082, -0.676,  0.215,  2.211, -2.219, 0]
    endPose1 = [-0.032, -0.635,  0.215,  2.211, -2.219, 0]
    viaPose2 = [-0.082, -0.597,  0.215,  2.211, -2.219, 0]
    endPose2 = [-0.134, -0.6357, 0.215,  2.211, -2.219, 0]
    pose2    = [-0.134, -0.6357, 0.232,  2.211, -2.219, 0]
    robot.movel((pose1), acc, vel)
    robot.movec((viaPose1), (endPose1), acc, vel)
    robot.movec((viaPose2), (endPose2), acc, vel)
    robot.movel((pose2), acc, vel)

def drawE(acc, vel, robot):
    pose1  = [-0.134, -0.577,  0.2143, 2.211, -2.219, 0]
    pose2  = [-0.029, -0.577,  0.2148, 2.211, -2.219, 0]
    pose3  = [-0.029, -0.577,  0.2148, 2.211, -2.219, 0]
    pose4  = [-0.029, -0.5317, 0.2146, 2.211, -2.219, 0]
    pose5  = [-0.029, -0.5317, 0.240,  2.211, -2.219, 0]
    pose6  = [-0.134, -0.528,  0.2267, 2.211, -2.219, 0]
    pose7  = [-0.134, -0.528,  0.2114, 2.211, -2.219, 0]
    pose8  = [-0.134, -0.5774, 0.2139, 2.211, -2.219, 0]
    pose9  = [-0.082, -0.577,  0.237,  2.211, -2.219, 0]
    pose10 = [-0.082, -0.577,  0.2148, 2.211, -2.219, 0]
    pose11 = [-0.082, -0.548,  0.2148, 2.211, -2.219, 0]
    pose12 = [-0.082, -0.548,  0.238,  2.211, -2.219, 0]
    robot.movel((pose1), acc, vel)
    robot.movels((pose2, pose3, pose4), acc, vel)
    robot.movels((pose5, pose6, pose7), acc, vel)
    robot.movels((pose8, pose9, pose10, pose11, pose12), acc, vel)

def writeDoe(acc, vel, robot):
    home(robot)
    startPose = [deg2rad(-86.86), deg2rad(-123.86), deg2rad(-50), deg2rad(-95.80), deg2rad(89.81), deg2rad(86.74)]
    pose1 = [-0.134, -0.635, 0.234, 2.211, -2.219, 0]
    pose2 = [-0.134, -0.573, 0.232, 2.211, -2.219, 0]
    pose3    = [-0.178, -0.634, 0.238,  2.211, -2.219, 0]
    pose4    = [-0.178, -0.634, 0.215,  2.211, -2.219, 0]
    viaPose1 = [-0.091, -0.775, 0.212,  2.211, -2.219, 0]
    endPose1 = [-0.006, -0.642, 0.215,  2.211, -2.219, 0]
    viaPose2 = [-0.080, -0.508, 0.2139, 2.211, -2.219, 0]
    endPose2 = [-0.175, -0.642, 0.215,  2.211, -2.219, 0]
    robot.movej((startPose), 0.8, 0.8)
    drawD(acc, vel, robot)
    robot.movel((pose1), acc, vel)
    drawO(acc, vel, robot)
    robot.movel((pose2), acc, vel)
    drawE(acc, vel, robot)
    robot.movels((pose3, pose4), acc, vel)
    robot.movec((viaPose1), (endPose1), acc, vel)
    robot.movec((viaPose2), (endPose2), acc, vel)

def unlockTool(relay_pin, t):
    relay_pin.write(1)
    time.sleep(t)

def lockTool(relay_pin, t):
    relay_pin.write(0)
    time.sleep(t)

def helloWorld():
    print("hello world")
