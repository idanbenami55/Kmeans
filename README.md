K-means Algorithm Implementation

Overview: The K-means algorithm is a popular clustering method used to partition N unlabeled observations into K distinct clusters, where K is a parameter of the method. In this assignment,
you will implement this algorithm in both Python and C.


K-means:
Given a set of N datapoints x1, x2, . . . , xN ∈ Rd, the goal is to group the data into K ∈ N
clusters, each datapoint is assigned to exactly one cluster and the number of clusters K is such
that 1 < K < N. Each cluster k is represented by its centroid, which is the mean µk ∈ Rd of the
cluster’s members.

![image](https://github.com/user-attachments/assets/f8eac703-d962-4f47-92c8-61bd387f3add)


we'll allow:
![image](https://github.com/user-attachments/assets/5fdeee49-fa07-4685-a87b-6c5c9d24900e)

using ϵ = 0.001, and if iter is not provided, default value is 200.

![image](https://github.com/user-attachments/assets/05aa4100-295f-417b-9cd6-61220e959265)


