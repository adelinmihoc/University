from PIL import Image
from matplotlib import image as matplot_image
from matplotlib import pyplot


# A
def a():
    image = Image.open('../images/other/1.jpg')
    print(image.format)
    print(image.mode)
    print(image.size)
    image.show()


# B
def b():
    data = matplot_image.imread('../images/other/1.jpg')
    # print(data.dtype)
    print(data.shape)
    pyplot.imshow(data)
    pyplot.show()


def c():
    image = Image.open('../images/other/1.jpg')
    print(image.size)
    image.thumbnail((100, 100))
    print(image.size)
    image = image.convert(mode='L')
    image.show()


c()



