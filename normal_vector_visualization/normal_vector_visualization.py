
from sklearn.decomposition import PCA
from matplotlib.patches import FancyArrowPatch
from mpl_toolkits.mplot3d import proj3d
#library imports
import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import KDTree

class Arrow3D(FancyArrowPatch):
    def __init__(self, xs, ys, zs, *args, **kwargs):
        FancyArrowPatch.__init__(self, (0,0), (0,0), *args, **kwargs)
        self._verts3d = xs, ys, zs

    def draw(self, renderer):
        xs3d, ys3d, zs3d = self._verts3d
        xs, ys, zs = proj3d.proj_transform(xs3d, ys3d, zs3d, renderer.M)
        self.set_positions((xs[0],ys[0]),(xs[1],ys[1]))
        FancyArrowPatch.draw(self, renderer)


X = np.array([[24,13,38],[8,3,17],[21,6,40],[1,14,-9],[9,3,21],[7,1,14],[8,7,11],[10,16,3],[1,3,2],
    [15,2,30],[4,6,1],[12,10,18],[1,9,-4],[7,3,19],[5,1,13],[1,12,-6],[21,9,34],[8,8,7],
  [1,18,-18],[15,8,25],[16,10,29],[7,0,17],[14,2,31],[3,7,0],[5,6,7]])
pca = PCA(n_components=3)

pca.fit(X)
eig_vec = pca.components_
# [0.90946569 0.08816839 0.00236591]
# Percentage of variance explain by last vector is less 0.2%

# This is the normal vector of minimum variance
normal = eig_vec[2, :]  # (a, b, c)
normal2 = eig_vec[1, :]
normal3 = eig_vec[0, :]
centroid = np.mean(X, axis=0)
# Every point (x, y, z) on the planerkrr should satisfy a*x+b*y+c*z = d
# Taking centroid as a point on the plane
d = -centroid.dot(normal)
# Draw plane
xx, yy = np.meshgrid(np.arange(np.min(X[:, 0]), np.max(X[:, 0])), np.arange(np.min(X[:, 1]), np.max(X[:, 1])))

z = (-normal[0] * xx - normal[1] * yy - d) * 1. / normal[2]

mean_x = np.mean(xx)
mean_y = np.mean(yy)
mean_z = np.mean(z)
# plot the surface
plt3d = plt.figure().gca(projection='3d')
plt3d.plot_surface(xx, yy, z, alpha=0.2)
plt3d.scatter(mean_x, mean_y, mean_z, edgecolor="b", marker='s')
a = Arrow3D([mean_x, normal[0]], [mean_y, normal[1]], [mean_z, normal[2]], mutation_scale=20, lw=3, arrowstyle="-|>", color="r")
b = Arrow3D([mean_x, normal2[0]], [mean_y, normal2[1]], [mean_z, normal2[2]], mutation_scale=20, lw=3, arrowstyle="-|>", color="r")
c = Arrow3D([mean_x, normal3[0]], [mean_y, normal3[1]], [mean_z, normal3[2]], mutation_scale=20, lw=3, arrowstyle="-|>", color="r")
a_ = [[mean_x, normal[0]], [mean_y, normal[1]], [mean_z, normal[2]]]
b_ = [[mean_x, normal2[0]], [mean_y, normal2[1]], [mean_z, normal2[2]]]
c_ = [[mean_x, normal3[0]], [mean_y, normal3[1]], [mean_z, normal3[2]]]
n_vector = np.cross(a_, b_)
n_vector_ = Arrow3D([mean_x, n_vector[0]], [mean_y, n_vector[1]], [mean_z, n_vector[2]], mutation_scale=20, lw=3, arrowstyle="-|>", color="b")
plt3d.add_artist(a)
plt3d.add_artist(b)
plt3d.add_artist(c)
plt3d.add_artist(n_vector_)
plt3d.scatter(*(X.T), edgecolors="r")
#plt3d.scatter(points[0], edgecolors="g")
plt.show()

