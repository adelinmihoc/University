# -*- coding: utf-8 -*-

import torch
import torch.nn.functional as F


class Net(torch.nn.Module):
    # the class for the network

    def __init__(self, n_feature, n_hidden, n_output):
        # we have two layers: a hidden one and an output one
        super(Net, self).__init__()
        self.hidden = torch.nn.Linear(n_feature, n_hidden)
        self.hidden2 = torch.nn.Linear(n_hidden, n_hidden)
        # self.hidden = torch.nn.Sequential(
        #     torch.nn.Linear(n_feature, n_hidden),
        #     torch.nn.ReLU(),
        #     torch.nn.Linear(n_hidden, n_hidden),
        #     # torch.nn.ReLU()
        # )
        self.output = torch.nn.Linear(n_hidden, n_output)

    def forward(self, x):
        # a function that implements the forward propagation of the signal
        # observe the relu function applied on the output of the hidden layer
        x = F.relu(self.hidden(x))
        x = self.hidden2(x)
        x = F.relu(x)
        # x = self.hidden(x)
        x = self.output(x)
        return x
