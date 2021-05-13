import cv2
import numpy as np
img = 0

def draw_circle(event, x, y, flags, param):
    global img
    if event == cv2.EVENT_LBUTTONDBLCLK:
        cv2.circle(img, (x, y), 100, (255, 0, 0), -1)

class Pc2Img():
    def __init__(self):
        self._img = 0

    def make_img(self):
        global img 
        print("make img")
        gray_img = np.zeros((300, 300, 1), np.uint8) # y , x
        img = gray_img
        cv2.namedWindow('Pc2Img')
        cv2.setMouseCallback('Pc2Img', draw_circle)
        while True:
            cv2.imshow('Pc2Img', gray_img)
            if cv2.waitKey(20) & 0xFF == 27:
                break   
        cv2.destroyAllWindows()

if __name__=="__main__":
    print("start")
    test = Pc2Img()
    test.make_img()

# while True:
#     cv2.imshow('image', img)
#     if cv2.waitKey(20) & 0xFF == 27:
#         break
# cv2.destroyAllWindows()