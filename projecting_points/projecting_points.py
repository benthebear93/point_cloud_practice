import pcl
import pcl.pcl_visualization
import numpy as np
import random
import pptk

def main():
    cloud = pcl.PointCloud()
    cloud_projected = pcl.PointCloud()

    points = np.zeros((5, 3), dtype=np.float32)
    RAND_MAX = 1.0
    for i in range(0, 5):
        points[i][0] = 1024 * random.random() / RAND_MAX
        points[i][1] = 1024 * random.random() / RAND_MAX
        points[i][2] = 1024 * random.random() / RAND_MAX
        
    # v = pptk.viewer(xyz)
    # v.attributes(rgb / 255., 0.5 * (1 + n))
    cloud.from_array(points)

    print('Cloud before projection: ')
    for i in range(0, cloud.size):
        print('x: ' + str(cloud[i][0]) + ', y : ' +
              str(cloud[i][1]) + ', z : ' + str(cloud[i][2]))
    proj = cloud.make_ProjectInliers()
    proj.set_model_type(pcl.SACMODEL_PLANE)
    cloud_projected = proj.filter()
    print("type :", type(cloud))
    print("size :", cloud.size)
    visualize(cloud);  
    print('Cloud after projection: ')
    for i in range(0, cloud_projected.size):
        print('x: ' + str(cloud_projected[i][0]) + ', y : ' + str(
            cloud_projected[i][1]) + ', z : ' + str(cloud_projected[i][2]))
    #visualize(cloud_projected);     

def visualize(pc_data):
    print("visualize start")
    #centred = pc_data - np.mean(pc_data, 0)
    #pc_centred = pcl.PointCloud()
    #pc_centred.from_array(centred)

    visual = pcl.pcl_visualization.CloudViewing()
    visual.ShowMonochromeCloud(pc_data,b'pc_data')
    v = True
    while v:
        v = not(visual.WasStopped())
if __name__ == "__main__":
    # import cProfile
    # cProfile.run('main()', sort='time')
    main()