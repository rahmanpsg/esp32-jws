Import("env")
print("Replace MKSPIFFSTOOL")
env.Replace(MKSPIFFSTOOL = "./mklittlefs")
