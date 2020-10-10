#Christopher Sahadeo
#816000772

from sklearn.datasets import make_blobs
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt


#1
X, y = make_blobs(n_samples=450, centers=4)

#2
distortions = []
for k in range(1,10):
    clf = KMeans(n_clusters=k)
    clf.fit(X)
    distortions.append(clf.inertia_)

plt.figure(figsize=(15, 10))
plt.title('Elbow Curve')
plt.plot(range(1,10), distortions)
plt.show()

#3
clf = KMeans(n_clusters=4)
clf.fit(X)

#4
print('Labels: \n{}'.format(clf.labels_))

#5
print('Cluster centers: \n{}'.format(clf.cluster_centers_))

#5
plt.figure(figsize=(15, 10))
plt.title('KMeans')
plt.scatter(X[:,0], X[:,1], c=clf.labels_)
plt.scatter(clf.cluster_centers_[:,0], clf.cluster_centers_[:,1], c='red')
plt.show()
