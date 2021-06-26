import glob
from abc import ABC

from torch.utils.data import Dataset
from torchvision import transforms
from torchvision.datasets.folder import pil_loader

device = 'cpu'


class ImageClassifierDataset(Dataset, ABC):
    def __init__(self, image_list, image_classes):
        self.images = []
        self.labels = []
        self.classes = list(set(image_classes))
        self.class_to_label = {c: i for i, c in enumerate(self.classes)}
        self.image_size = 224
        self.transforms = transforms.Compose([
            # transforms.Resize(self.image_size),
            transforms.Resize((self.image_size, self.image_size)),
            transforms.CenterCrop(self.image_size),
            transforms.ToTensor(),
            transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))
        ])
        for image, image_class in zip(image_list, image_classes):
            transformed_image = self.transforms(image)
            self.images.append(transformed_image)

            label = self.class_to_label[image_class]
            self.labels.append(label)

    def __getitem__(self, index):
        return self.images[index], self.labels[index]

    def __len__(self):
        return len(self.images)


def get_image_list_and_classes(path):
    size = 200, 200
    img_list = []
    img_classes = []
    for infile in glob.glob(path + "/men/*.jpg"):
        with pil_loader(infile) as im:
            # im.thumbnail(size)
            img_list.append(im)
            img_classes.append(1)
    for infile in glob.glob(path + "/women/*.jpg"):
        with pil_loader(infile) as im:
            # im.thumbnail(size)
            img_list.append(im)
            img_classes.append(1)
    for infile in glob.glob(path + "/other/*.jpg"):
        with pil_loader(infile) as im:
            # im.thumbnail(size)
            img_list.append(im)
            img_classes.append(0)
    return img_list, img_classes
