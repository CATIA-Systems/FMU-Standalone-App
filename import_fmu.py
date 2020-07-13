import sys
import shutil
import os
from fmpy import *

fmu_filename = sys.argv[1]

model_name = os.path.basename(fmu_filename)
model_name, _ = os.path.splitext(model_name)

project_dir = os.path.dirname(__file__)
unzip_dir = os.path.join(project_dir, 'model')
header_file = os.path.join(project_dir, 'include', 'model.h')

model_description = read_model_description(fmu_filename)

if os.path.isdir(unzip_dir):
    print("Removing %s..." % unzip_dir)
    shutil.rmtree(unzip_dir)

print("Extracting %s to %s..." % (fmu_filename, unzip_dir))
extract(fmu_filename, unzip_dir)

print("Generating %s from %s" % (header_file, fmu_filename))

variables = dict((v.name, v.valueReference) for v in model_description.modelVariables)

with open(header_file, 'w') as f:
    f.write('#pragma once\n')
    f.write('// Generated from %s (%s)\n' % (fmu_filename, model_description.generationDateAndTime))
    f.write('\n')
    f.write('# define FMI2_FUNCTION_PREFIX %s_\n' % model_description.coSimulation.modelIdentifier)
    f.write('# define GUID                 "%s"\n' % model_description.guid)
    f.write('# define VR_T                 %s\n' % variables['T'])
    f.write('# define VR_U                 %s\n' % variables['u'])
    f.write('# define VR_TAMB              %s\n' % variables['TAmb'])

print("Done.")
