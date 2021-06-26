import torch
import torch.nn.functional as F
import matplotlib.pyplot as plt
import numpy as np

import myModel

# x = torch.unsqueeze(torch.linspace(-1, 1, 100), dim=1)

# Creates a one-dimensional tensor of size 100 whose values are evenly spaced
# from -1 to 1, inclusive, and is placing the values in a tensor like
# so x = [ [-1], [-0.98], ..., [0.98]. 1]

# print(x)

# y = x.pow(2) + 0.2
# the function to be optimised

# print(y)

dataset = torch.load("mydataset.dat")
# print(dataset)
x = torch.empty(0, 2)
y = torch.empty(0, 1)
for data in dataset:
    x = torch.vstack((x, torch.tensor([data[0], data[1]])))
    y = torch.vstack((y, data[2]))


# we set up the lossFunction as the mean square error
lossFunction = torch.nn.MSELoss()

# we create the ANN
ann = myModel.Net(n_feature=2, n_hidden=10, n_output=1)

print(ann)
# we use an optimizer that implements stochastic gradient descent 
optimizer_batch = torch.optim.SGD(ann.parameters(), lr=0.02)

# we memorize the losses for some graphics
loss_list = []
avg_loss_list = []

# we set up the environment for training in batches  
batch_size = 255
n_batches = int(len(x) / batch_size)
print(n_batches)

for epoch in range(10000):

    for batch in range(n_batches):
        # we prepare the current batch  -- please observe the slicing for tensors
        batch_X = x[batch * batch_size:(batch + 1) * batch_size, ]
        batch_y = y[batch * batch_size:(batch + 1) * batch_size, ]

        # we compute the output for this batch
        prediction = ann(batch_X)

        # we compute the loss for this batch
        loss = lossFunction(prediction, batch_y)

        # we save it for graphics
        loss_list.append(loss.item())

        # we set up the gradients for the weights to zero (important in pytorch)
        optimizer_batch.zero_grad()

        # we compute automatically the variation for each weight (and bias) of the network
        loss.backward()

        # we compute the new values for the weights
        optimizer_batch.step()

        # we print the loss for all the dataset for each 10th epoch
    if epoch % 500 == 0:
        y_pred = ann(x)
        loss = lossFunction(y_pred, y)
        print('\repoch: {}\tLoss =  {:.5f}'.format(epoch, loss.item()))

    # Specify a path
filepath = "myNet.pt"
print("state dict is\n")
print(ann.state_dict())
# save the model to file
torch.save(ann.state_dict(), filepath)

# visualise the parameters for the ann (aka weights and biases)
# for name, param in ann.named_parameters():
#     if param.requires_grad:
#         print (name, param.data)

plt.plot(loss_list)
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.show()
