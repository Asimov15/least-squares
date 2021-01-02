#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib
matplotlib.use('Agg')

from pylab import rcParams
rcParams['figure.figsize'] = 20, 9

import argparse
import sys
import codecs
import json, requests
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import datetime
import numpy as np
from numpy import arange
from datetime import datetime, timedelta, tzinfo, date
from dateutil import tz
from matplotlib import style
import matplotlib.ticker as ticker

#from matplotlib.ticker import MultipleLocator, FormatStrFormatter
#from matplotlib.dates import DayLocator, HourLocator, DateFormatter, drange
import csv
import math

#plt.style.use('seaborn-whitegrid')
x = []
y = []
e = []
f = []

with open('copper3.csv') as csv_file:
	csv_reader = csv.reader(csv_file, delimiter=',')
	line_count = 0

	for row in csv_reader:
		if line_count == 0:
			print('{0}'.format(", ".join(row)))
		else:
			print('{0}, {1}'.format(row[0], row[1]))
			x.append(row[0])
			y.append(row[1])
			e1 = float(row[0])
			e.append(3.934 + -0.0405 * e1 + 0.0135 * e1 * e1)
#			e.append(3.9133049544519541 + -0.0077442615344973201 * e1 + 0.0001773653175627696 * e1 * e1 + -1.8125173542458588e-06 * pow(e1,3))
#			f.append(3.90435 - 0.00614011 * e1 +  0.000121733 * e1 * e1 + -1.31661e-06 * pow(e1,3))
		line_count += 1

fig, ax = plt.subplots()

#ax.xaxis.set_major_formatter(plt.NullFormatter())

plt.plot(x, y, 'o', color='black')
plt.plot(x, e, 'o', color='blue')
#plt.plot(x, f, 'o', color='green')
#ax.yaxis.set_major_locator(plt.MaxNLocator(7))
#ax.xaxis.set_major_locator(plt.MaxNLocator(7))
#ax.xaxis.set_major_locator(plt.LinearLocator(numticks=5))
ax.xaxis.set_major_locator(plt.MultipleLocator(10))
ax.yaxis.set_major_locator(plt.MultipleLocator(10))
#ax.set_ylim(ax.get_ylim()[::-1])
ax.set_ylim(ymin=3)
plt.gca().invert_yaxis()
plt.savefig("price.png")

