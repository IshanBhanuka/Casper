
from controller import Robot
TIMESTEP =64

def driver(arr):
    if arr[1]:
       return "turn left"
    elif arr[0]:
       return "turn right" 
    elif arr[0 and 1]:
       return "GOOO"   
    else:
       return "GOOO"

robot = Robot()

if __name__ == '__main__':

    #---configuring motors--
    rightmotor = robot.getDevice('MotorR')
    leftmotor = robot.getDevice('MotorL')  
    
    rightmotor.setPosition(float('inf'))
    leftmotor.setPosition(float('inf'))
    
    rightmotor.setVelocity(0.0)
    leftmotor.setVelocity(0.0)
    
    #---configuring snesors--
    #front = robot.getDevice('front_sensor')
    left = robot.getDevice('left_sensor')
    right = robot.getDevice('right_sensor')
    
    #front.enable(TIMESTEP)
    left.enable(TIMESTEP) 
    right.enable(TIMESTEP)
    
    

while robot.step(TIMESTEP) != -1:
        # Read the sensors:
        # Enter here functions to read sensor data, like:
        #  val = ds.getValue()
        speedR = 1.0
        speedL = 1.0
        
        #--reading the sensors
        val_L = left.getValue()
        val_R = right.getValue()
        
        Wall = [300 < val_L < 500, 300 < val_R < 500]
        print(Wall)
        
        descision = driver(Wall)
        
        if descision == "turn right":
           speedR = -10.0 
           speedL = 10.0
        
        if descision == "turn left":
            speedR = 10.0
            speedL = -10.0
        if descision == "GOOO":
            speedR = 10.0
            speedL = 10.0
        
        
        
        rightmotor.setVelocity(-1*speedR)
        leftmotor.setVelocity(-1*speedL)
        
        print(val_L,val_R)
        pass


