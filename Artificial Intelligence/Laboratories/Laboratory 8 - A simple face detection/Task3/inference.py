import numpy as np
import torch
import torchvision
from torch.utils.data import DataLoader

from model_train import SimpleNet
import classifier
from torchvision.transforms import transforms
import matplotlib.pyplot as plt


# we load the model
filepath = "faces_model_11.model"
model = SimpleNet(2)
# print(ann)

model.load_state_dict(torch.load(filepath))
model.eval()

image_list, image_classes = classifier.get_image_list_and_classes("../manual_test_images")
test_set = classifier.ImageClassifierDataset(image_list, image_classes)
test_loader = DataLoader(test_set, batch_size=1, shuffle=True, num_workers=0)
test_transformations = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
])


def imshow(img, label):
    img = img / 2 + 0.5
    npimg = img.numpy()
    plt.imshow(np.transpose(npimg, (1, 2, 0)))
    plt.title(label)
    plt.show()


images, labels = next(iter(test_loader))
# print(labels.data)

# imshow(torchvision.utils.make_grid(images[0]))


isHuman = torch.Tensor([1])
# print(isHuman)


for i, (images, labels) in enumerate(test_loader):
    outputs = model(images)
    _, prediction = torch.max(outputs.data, 1)
    # print(prediction.data)
    if prediction == isHuman:
        imshow(torchvision.utils.make_grid(images), "HUMAN")
    else:
        imshow(torchvision.utils.make_grid(images), "NOT HUMAN")
