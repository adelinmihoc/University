import torch

n = 1000
mini = -10
maxi = 10

random_points = (mini - maxi) * torch.rand(n, 2) + maxi

PI = torch.tensor(3.14159265359)

points = []
results = []
for point in random_points:
    x1 = point[0]
    x2 = point[1]
    # f_(x1, x2) = sin(x1 + x2/pi)
    r = torch.sin(torch.addcdiv(x1, x2, PI))
    points.append(point)
    results.append(r)

points = torch.stack(points)
results = torch.stack(results)

database = torch.column_stack((points, results))
# print(database)
torch.save(database, "mydataset.dat")
