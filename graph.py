# python script for graphing data

from matplotlib import pyplot as plt
from pandas import read_csv

data = read_csv("connectivity.txt");

plt.plot(data['prob'],data['connected']);
plt.title("Percent of Skip Lists that remain Connected vs.\nthe Probability of Failure for Each Node")
plt.xlabel("Percent Probability that Any Given Node will Fail");
plt.ylabel("Percent of Lists that are Connected")
plt.figure()

data = read_csv("inputSize.txt");

plt.plot(data['size'],data['5%'],label = '5%');
plt.plot(data['size'],data['10%'],label = '10%');
plt.plot(data['size'],data['15%'],label = '15%');
plt.plot(data['size'],data['20%'],label = '20%');
plt.legend();
plt.title("Percent of Skip Lists that Remain Connected vs.\n the Number of Words Read from\na File at Constant Failure Probabilities");
plt.xlabel("Size of Input file in Words");
plt.ylabel("Percent of Lists that are Connected");
plt.figure();

data = read_csv("insertTime.txt");

plt.plot(range(100000,1100000,100000),data['list'],label = "List");
plt.plot(range(100000,1100000,100000),data['tree'],label = "Tree");
plt.title("Insert Times Compared Between a BST and a Skip List\nwith Increasing Input Size");
plt.ylabel("Time (s)");
plt.xlabel("Input Size (words)");
plt.legend();
plt.figure();

data = read_csv("searchTime.txt");

plt.plot(range(100000,1100000,100000),data['list'],label = "List");
plt.plot(range(100000,1100000,100000),data['tree'],label = "Tree");
plt.title("Search Times Compared Between a BST and a Skip List\nwith Increasing Input Size");
plt.ylabel("Time (ms)");
plt.xlabel("Input Size (words)");
plt.legend();
plt.figure();

data = read_csv("removeTime.txt");

plt.plot(range(100000,1100000,100000),data['list'],label = "List");
plt.plot(range(100000,1100000,100000),data['tree'],label = "Tree");
plt.title("Removal Times Compared Between a BST and a Skip List\nwith Increasing Input Size");
plt.ylabel("Time (ms)");
plt.xlabel("Input Size (words)");
plt.legend();

plt.show();

