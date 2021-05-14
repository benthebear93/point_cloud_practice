#!/usr/bin/env python2
import pcl
import pcl.pcl_visualization
import numpy as np
import math
import rospy
from sensor_msgs.msg import PointCloud2
import sensor_msgs.point_cloud2 as pc2
import cv2
import matplotlib.pyplot as plt
file_path = '/home/benlee/Desktop/git/point_cloud_practice/pcd_files/data'

class Pc2Img():
    def __init__(self):
        self._pc_data = 0
        self._cloud_projected = pcl.PointCloud()
        self._pc_size = 0
        self._img_x_size = 0
        self._img_y_size = 0
        self._img_z_size = 0
        self._dis_two_point = 0.000917/4
        self._img_x = []
        self._img_y = []
        self._img_z = []
        self._img_xy = []
        self._min_x = 0
        self._min_y = 0
        self._min_z = 0

    def mouse_event_handle(self, event, x,y,flags, param):
        img = param[0]
        if event==cv2.EVENT_LBUTTONDBLCLK:
            
            distance =img[y,x,0]
            if(distance==0):
                print("select point is empty search nearest point")
                for i in range(-2, 3):
                    for j in range(-2, 3):
                        #print 'y+j', y+j,'x-j', x+i
                        distance = img[y+j,x-j,0]
            print distance
            print 'x :', x*self._dis_two_point + self._min_x, 'y :', y*self._dis_two_point + self._min_y, 'z :', ((distance-140)+ self._min_z)/1500 
            cv2.circle(img, (x, y), 10, (255, 0, 0), -1)
            cv2.imshow("Pc2Img", img)
            
    def read_pcd(self):
        # print("read pcd")
        profile_pcd = pcl.load(file_path + '/passfilter_pc.pcd')
        self._pc_data = profile_pcd
        self._pc_size = profile_pcd.size

    def pc2xy(self):
        for i in range(self._pc_size):
            self._img_x.append(self._pc_data[i][0])
            self._img_y.append(self._pc_data[i][1])
            self._img_z.append(self._pc_data[i][2])
            #pc data to x,y,z array

        max_x = round(max(self._img_x),5)
        min_x = round(min(self._img_x),5)
        max_y = round(max(self._img_y),5)
        min_y = round(min(self._img_y),5)
        max_z = round(max(self._img_z),5)
        min_z = round(min(self._img_z),5)
        self._min_x = min_x
        self._min_y = min_y
        # print(min_x)
        # print(min_y)
        self._min_z = min_z
        #find min and max to set start and end of img

        self._img_x_size = max_x - min_x
        self._img_y_size = max_y - min_y 
        self._img_z_size = max_z - max_z
        
    def visualize(self, _pc_data):
        print("visualize start")
        #centred = _pc_data - np.mean(_pc_data, 0)
        #pc_centred = pcl.PointCloud()
        #pc_centred.from_array(centred)

        visual = pcl.pcl_visualization.CloudViewing()
        visual.ShowMonochromeCloud(_pc_data,b'_pc_data')
        v = True
        while v:
            v = not(visual.WasStopped())

    def projection_z(self):
        print("Cloud projecting to Z")
        proj = self._pc_data.make_ProjectInliers()
        proj.set_model_type(pcl.SACMODEL_PLANE)
        self._cloud_projected = proj.filter()
        # print 'type :', type(self._cloud_projected)
        # print 'size :', self._cloud_projected.size
        # print 'x pixel range :', self._img_x_size, 'y pixel range', self._img_y_size
        # print "img size :", round(self._img_x_size/self._dis_two_point), round(self._img_y_size/self._dis_two_point)
        self._img_x_size = round(self._img_x_size/self._dis_two_point)
        self._img_y_size = round(self._img_y_size/self._dis_two_point)

        #self.visualize(_cloud_projected)

    def make_img(self):
        print("                                            ")
        print("==============start making img==============")
        print 'one pixel : 0.23mm' 
        print 'set tool size'
        height = int(round(self._img_y_size))
        width  = int(round(self._img_x_size))
        print "h :", height, "w :", width
        # height = 659 , width = 790

        gray_img = np.zeros((height, width, 1), np.uint8) # y , x
        non_gray_img = np.zeros((height, width, 1), np.uint8) # y , x
        # black background image making , size : 755*894
        # start position of (0,0)

        ker3x3 = np.array([[1, 1, 1], [1,1,1],[1,1,1]])
        
        for i in range(0, self._pc_size):
            start_pos_x = self._min_x 
            start_pos_y = self._min_y
            min_x = start_pos_x
            min_y = start_pos_y
            mimun_z     = self._min_z
            pixel_x = int(round((self._pc_data[i][0] - start_pos_x)/self._dis_two_point))
            pixel_y = int(round((self._pc_data[i][1] - start_pos_y)/self._dis_two_point))
            range_z = (self._pc_data[i][2] - mimun_z)*1500
            #multipy 1500 for conversion of range z to 0~255 

            if(pixel_x> width-1):
                pixel_x = pixel_x -1
            if(pixel_y>height-1):
                pixel_y=pixel_y-1
                
            gray_img.itemset((pixel_y, pixel_x, 0), 140+int(range_z)) #140 for minumum 
            for i in range(-2, 3):
                for j in range(-2, 3):
                    pixel_y = pixel_y+j
                    pixel_x = pixel_x+i
                    #print 'y+j', pixel_y+j,'x-j', pixel_x+i
                    gray_img.itemset((pixel_y, pixel_x, 0), 140+int(range_z)) #140 for minumum 
            # for j in range(0, 3):
            #     pixel_x = pixel_x+1
            #     if(pixel_x> width-1):
            #         pixel_x = pixel_x -1
            #     pixel_y = pixel_y
            #     if(pixel_y>height-1):
            #         pixel_y=pixel_y-1
                #print("x : ", pixel_x, "y : ", pixel_y)
                #gray_img.itemset((pixel_y, pixel_x, 0), 140+int(range_z))
            #print("range_z z : ", range_z, "data :", self._pc_data[i][0], "test :" ,pixel_x*0.000917/4 + min_x)
            #print("range_z z : ", range_z, "data :", self._pc_data[i][2], "test :" ,range_z/1500 + mimun_z)
            #match 

        img = gray_img
        cv2.namedWindow('Pc2Img')
        cv2.setMouseCallback('Pc2Img', self.mouse_event_handle, param = [img])
        while True:
            cv2.imshow('Pc2Img', img)
            if cv2.waitKey(20) & 0xFF == 27:
                break   
        cv2.destroyAllWindows()

if __name__=="__main__":
    test = Pc2Img()
    test.read_pcd()
    test.pc2xy()
    test.projection_z()
    test.make_img()
    #test.visualize()