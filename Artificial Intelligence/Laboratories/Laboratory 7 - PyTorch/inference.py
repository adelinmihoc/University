# -*- coding: utf-8 -*-
"""
Created on Tue Apr 27 14:20:51 2021

@author: tudor
"""

import torch
import myModel

# we load the model
filepath = "myNet.pt"
ann = myModel.Net(2, 10, 1)
print(ann)

ann.load_state_dict(torch.load(filepath))
ann.eval()

# visualise the parameters for the ann (aka weights and biases)
# for name, param in ann.named_parameters():
#     if param.requires_grad:
#         print (name, param.data)

while True:
    x1 = float(input("x1 = "))
    x2 = float(input("x2 = "))
    x = torch.tensor([x1, x2])
    print(ann(x).tolist())
    print(f'correct: {torch.sin(torch.addcdiv(torch.tensor(x1), torch.tensor(x2), torch.tensor(3.14159265359)))}')
