import csv

import matplotlib.pyplot as plt
import numpy as np
from math import sqrt

K = 4
points = []


class Point:
    def __init__(self, label, x, y):
        self.label = label
        self.x = float(x)
        self.y = float(y)

    def __str__(self):
        return "lab: " + str(self.label) + " | x: " + str(self.x) + " | y: " + str(self.y)


def euclidean_distance(p1, p2):
    return sqrt((p1[0]-p2[0])**2 + (p1[1]-p2[1])**2)


def main():
    read_points()

    random_centroids = np.random.choice(points, K, replace=False)
    print("============================")
    print("initial K points selected:\n")
    for x in random_centroids:
        print(x)
    print("============================")
    centroids = [(rc.x, rc.y) for rc in random_centroids]
    print("initial centroids: " + str(centroids))
    print("============================")

    while True:
        clusters = create_cluster(centroids)

        centroids_old = centroids
        centroids = recompute_centroids(clusters)

        if is_converged(centroids_old, centroids):
            break

    plot(clusters)
    clusters_score(clusters)


def create_cluster(centroids):
    clusters = [[] for _ in range(K)]
    for point in points:
        index = closest_cluster((point.x, point.y), centroids)
        clusters[index].append(point)
    return clusters


def closest_cluster(point, centroids):
    min_dist = 100000000
    closest = None
    for i in range(len(centroids)):
        if euclidean_distance(point, centroids[i]) < min_dist:
            min_dist = euclidean_distance(point, centroids[i])
            closest = i
    return closest


def recompute_centroids(clusters):
    centroids = [(0, 0) for _ in range(K)]
    for i in range(K):
        mean_x = 0
        mean_y = 0
        for point in clusters[i]:
            mean_x += point.x
            mean_y += point.y
        mean_x = mean_x/len(clusters[i])
        mean_y = mean_y/len(clusters[i])
        cluster_mean = (mean_x, mean_y)
        centroids[i] = cluster_mean
    return centroids


def is_converged(centroids_old, centroids_new):
    flag = True
    for i in range(K):
        if euclidean_distance(centroids_old[i], centroids_new[i]) != 0:
            flag = False
    return flag


def read_points():
    with open('dataset.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                line_count += 1
            else:
                points.append(Point(row[0], row[1], row[2]))
                line_count += 1


def clusters_score(clusters):
    print("============================")
    for i in range(K):
        TP = 0
        TN = 0
        FP = 0
        FN = 0
        label = get_cluster_label(clusters[i])

        for p in clusters[i]:
            if p.label == label:
                TP += 1
            else:
                FP += 1

        for p in points:
            if p not in clusters[i]:
                if p.label != label:
                    TN += 1
                else:
                    FN += 1

        accuracy = (TP + TN) / (TP + TN + FP + FN)
        precision = TP / (TP + FP)
        rappel = TP / (TP + FN)
        try:
            score = 2 * precision * rappel / (precision + rappel)
        except ZeroDivisionError:
            score = "div error"

        color = ""
        if label == "A":
            color = "blue"
        if label == "B":
            color = "red"
        if label == "C":
            color = "orange"
        if label == "D":
            color = "green"

        print("Accuracy for cluster " + color + " = " + str(accuracy))
        print("Precision for cluster " + color + " = " + str(precision))
        print("Rappel for cluster " + color + " = " + str(rappel))
        print("Score for cluster " + color + " = " + str(score))
        print("----------------------------")


def get_cluster_label(cluster):
    labels = {'A': 0, 'B': 0, 'C': 0, 'D': 0}
    for p in cluster:
        labels[p.label] += 1

    max_label = max(labels, key=lambda k: labels[k])
    return max_label


def plotCSVData():
    xA = np.array([])
    yA = np.array([])

    xB = np.array([])
    yB = np.array([])

    xC = np.array([])
    yC = np.array([])

    xD = np.array([])
    yD = np.array([])
    read_points()
    for point in points:
        if point.label == 'A':
            xA = np.append(xA, point.x)
            yA = np.append(yA, point.y)
        if point.label == 'B':
            xB = np.append(xB, point.x)
            yB = np.append(yB, point.y)
        if point.label == 'C':
            xC = np.append(xC, point.x)
            yC = np.append(yC, point.y)
        if point.label == 'D':
            xD = np.append(xD, point.x)
            yD = np.append(yD, point.y)
    plt.scatter(xA, yA, color='blue')
    plt.scatter(xB, yB, color='red')
    plt.scatter(xC, yC, color='orange')
    plt.scatter(xD, yD, color='green')
    plt.show()


def plot(clusters):
    xA = np.array([])
    yA = np.array([])

    xB = np.array([])
    yB = np.array([])

    xC = np.array([])
    yC = np.array([])

    xD = np.array([])
    yD = np.array([])

    for i in range(K):
        for j in range(len(clusters[i])):
            label = get_cluster_label(clusters[i])
            if label == "A":
                xA = np.append(xA, clusters[i][j].x)
                yA = np.append(yA, clusters[i][j].y)
            if label == "B":
                xB = np.append(xB, clusters[i][j].x)
                yB = np.append(yB, clusters[i][j].y)
            if label == "C":
                xC = np.append(xC, clusters[i][j].x)
                yC = np.append(yC, clusters[i][j].y)
            if label == "D":
                xD = np.append(xD, clusters[i][j].x)
                yD = np.append(yD, clusters[i][j].y)
    plt.scatter(xA, yA, color='blue')
    plt.scatter(xB, yB, color='red')
    plt.scatter(xC, yC, color='orange')
    plt.scatter(xD, yD, color='green')

    plt.show()


plotCSVData()
main()
