# -*- coding: utf-8 -*-
"""
In this file your task is to write the solver function!
"""

import numpy as np


def solver(t, w):
    """
    Parameters
    ----------
    t : TYPE: float
        DESCRIPTION: the angle theta
    w : TYPE: float
        DESCRIPTION: the angular speed omega

    Returns
    -------
    F : TYPE: float
        DESCRIPTION: the force that must be applied to the cart
    or
    
    None :if we have a division by zero
    """

    t_set = [(-50, -40, -25), (-40, -25, -10), (-20, -10, 0), (-5, 0, 5), (0, 10, 20),
             (10, 25, 40), (25, 40, 50)]
    w_set = [(-10, -8, -3), (-6, -3, 0), (-1, 0, 1), (0, 3, 6), (3, 8, 10)]
    f_weighs = [-32, 24, -16, -8, 0, 8, 16, 24, 32]

    table = np.zeros((7, 5))

    for i in range(7):  # theta
        # calculate niu for theta
        # triangular
        a = t_set[i][0]
        b = t_set[i][1]
        c = t_set[i][2]
        niu_t = max(0, min((t - a) / (b - a), 1, (c - t) / (c - b)))
        for j in range(5):  # omega
            # calculate niu for omega
            # triangular
            a = w_set[j][0]
            b = w_set[j][1]
            c = w_set[j][2]
            niu_w = max(0, min((w - a) / (b - a), 1, (c - w) / (c - b)))

            table[i][j] = min(niu_t, niu_w)

    diags = [table[::-1, :].diagonal(i) for i in range(-table.shape[0] + 1, table.shape[1])]
    diags = [n.tolist() for n in diags]

    f_set = [max(diags[0][0], max(n for n in diags[1]))]
    for i in range(2, 9):
        f_set.append(max(n for n in diags[i]))
    f_set.append(max(diags[-1][0], max(n for n in diags[-2])))

    F = 0

    for i in range(0, len(f_set)):
        F += f_weighs[i] * f_set[i]

    try:
        F = F / sum(f_set)
        return F
    except ZeroDivisionError:
        return None
