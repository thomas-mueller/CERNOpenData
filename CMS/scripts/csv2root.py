#!/usr/bin/env python
# -*- coding: utf-8 -*-

import argparse
import csv
import numpy
import os
import ROOT


def get_type(value_string):
	for python_type, root_type in zip([int, float, str], ["I", "D", "C"]):
		try:
			value = python_type(value_string)
			return python_type, root_type
		except:
			pass
	raise Exception()

def create_branch(tree, name, python_type, root_type):
	value = numpy.zeros(1, dtype=python_type)
	tree.Branch(name, value, "%s/%s" % (name, root_type))
	return value

def csv2root(csv_filename):
	root_filename = os.path.splitext(csv_filename)[0]+".root"
	print "Converting", csv_filename, "to", root_filename, "..."
	with open(csv_filename, "rb") as csv_file:
		csv_reader = csv.reader(csv_file)
		csv_content = list(csv_reader)
		
		root_file = ROOT.TFile.Open(root_filename, "RECREATE")
		root_tree = ROOT.TTree("events", os.path.basename(csv_filename))
		
		python_types = []
		branch_values = []
		print "\t", csv_content[0]
		for header, value in zip(csv_content[0], csv_content[1]):
			python_type, root_type = get_type(value)
			python_types.append(python_type)
			branch_values.append(create_branch(root_tree, header, python_type, root_type))
		
		for event in csv_content[1:]:
			for python_type, branch_value, value in zip(python_types, branch_values, event):
				branch_value[0] = python_type(value)
			root_tree.Fill()
		
		root_file.Write()
		root_file.Close()

if __name__ == "__main__":

	parser = argparse.ArgumentParser(description="Convert CSV file(s) into ROOT tree.")
	parser.add_argument("input_files", nargs="+", help="Input CSV files.")
	args = parser.parse_args()
	
	for input_file in args.input_files:
		csv2root(input_file)

