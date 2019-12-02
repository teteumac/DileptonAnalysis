# Getting started on HTCondor (specifically for T2_BR_UERJ users)

To use HTCondor on your analysis, you mainly need two files. An executable file and a submission file. I also use a file to 
list all the ntuples that I want to use.
The last one is optional, but I'll explain everything considering the usage of this file too.

*PS.: Despite the fact that I have a lot of files in this folder, the majority is just the same file with different options.
On this tutorial I'll use the MC one to explain.*

## Important things to clarify before we start

1. All your files that you want to read using HTCondor at T2_BR_UERJ HAVE to be located at */mnt/hadoop/cms/store/user/*
(I'll say only *hadoop* for now on).

2. The files that you use to analyze/process the files that you are going to read DON'T NEED to be located at *hadoop*.
I highly recommend you to keep these files at your */home* folder, because is not so simple to manage files in *hadoop*.  

So, summarizing, put ntuples, samples, files you want to read at *hadoop* and files you want to execute at */home*.

## Executable file 

The executable file is where you want to describe what the HTCondor have to do when you runs it. For example, my 
*sub_MC.sh* :

```
#!/bin/bash

file=$1
echo "Input file: $file"
echo "Listing input file:"
ls -la $file
echo "Listing current dir:"
ls -la .
pwd

echo 'Running'
root -b <<EOS
.L ntp1-miniaod_MC.C
run("/mnt/hadoop/cms/store/user/malvesga/MC_signal/$file", "$file")
.q
EOS
```

where we have:

1. #!/bin/bash : The shebang is a directive to the loader to use the program which is specified after the #! as the 
interpreter for the file in question when you try to execute it.

2. file=$1 : This line is going to take the arguments from your file that have the list of files.

3. echo "..." : Just a command to return me which stage of the executable the HTCondor are in.

4. ls -la $file, ls -la, pwd : Just to confirm that I'm doing everything on the way that I want.

5. root -b -l <<EOS ... EOS : That is what I want the HTCondor to do for me. Just for a better understading, 
I open the root client, load my analyzer (that can be located at your */home* folder) and use this run function, 
where the first "" is the file I want to read (that have to be located at *hadoop*) and the second "" is the output file (that can be located at your */home*).

## Submission file

The submission file is something like this: 

```
executable = sub_MC.sh

Universe   = grid

output     = test_MC/output_$(ProcId).out
error      = test_MC/output_$(ProcId).err
log        = test_MC/output_$(ProcId).log

getenv     = True
should_transfer_files = YES
when_to_transfer_output = ON_EXIT_OR_EVICT
transfer_input_files = /home/malvesga/CMSSW_10_6_5/src/workspace/Dilepton_15_11_19/ntp1.h , /home/malvesga/CMSSW_10_6_5/src/workspace/Dilepton_15_11_19/ntp1-miniaod_MC.C 

x509userproxy = /tmp/x509up_u10024
use_x509userproxy = true

+JobFlavour = "microcentury"

grid_resource = condor osgce2.hepgrid.uerj.br osgce2.hepgrid.uerj.br:9619
+remote_jobuniverse = 5
+remote_requirements = True
+remote_ShouldTransferFiles = "YES"
+remote_WhenToTransferOutput = "ON_EXIT"

accounting_group_user = malvesga
accounting_group = group_uerj

queue arguments from ListOfFiles_MC.txt
```

where we have : 

1. 


### Installing

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```
