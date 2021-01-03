#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib
matplotlib.use('Agg')

from pylab import rcParams
rcParams['figure.figsize'] = 20, 9

import matplotlib.pyplot as plt
from matplotlib import style
import matplotlib.ticker as ticker
import csv
import math

time_seq1 = []
time_seq2 = []
price_seq = []
fit_price_seq = []

time_index = 0.0
price_element = 0.0

with open('coefficients.csv') as csv_file:
	reader = csv.reader(csv_file)
	csv_reader = csv.reader(csv_file, delimiter=',')
	for coefficients in csv_reader:
		i = 0
	print("number of coefficients = {0}".format(len(coefficients)))
	
with open('copper4.csv') as csv_file:
	csv_reader = csv.reader(csv_file, delimiter=',')
	line_count = 0

	for row in csv_reader:
		if line_count == 0:
			print('{0}'.format(", ".join(row)))
		else:
			time_index = float(row[0])
			price_element = float(row[1])
			print('{0}, {1}'.format(time_index, price_element))

			if time_index < 50.0:
				time_seq1.append(float(time_index))
				price_seq.append(price_element)

			e1 = float(time_index)
			fit_y = 0
			index = 0
			for factor in coefficients:
				fit_y = fit_y + float(factor) * pow(e1,index)
				index = index + 1
			print(fit_y)
			fit_price_seq.append(fit_y)
			time_seq2.append(time_index)
		line_count += 1
		if line_count > 50:
			break

fig, ax = plt.subplots()
plt.plot(time_seq1, price_seq, 'o-', color='black', label='Copper Market Data')
plt.plot(time_seq2, fit_price_seq, 'o-', color='blue', label='Fitted Curve {0}th Degree Polynomial'.format(len(coefficients)))
legend = ax.legend(loc='upper center', shadow=True, fontsize='x-large')
plt.savefig("price.png")
