import cv2
import numpy as np

img = cv2.imread('/home/benlee/Desktop/Black.png', cv2.IMREAD_COLOR)
print("shape:" + str(img.shape))
print("size:" + str(img.size))
print("dtype:" + str(img.dtype))

count = 0
height, width, channel = img.shape
print("chnnel :", channel)
img_heart = np.zeros((height, width, channel), np.uint8)
