# Getting started on HTCondor (specifically for T2_BR_UERJ users)

To use HTCondor on your analysis, you mainly need two files. An executable file and a submission file. I also use a file to 
list all the ntuples that I want to use.
The last one is optional, but I'll explain everything considering the usage of this file too.

*PS.: Despite the fact that I have a lot of files in this folder, the majority is just the same file with different options.
On this tutorial I'll use the MC one to explain.*

## Important things to clarify before we start

1. All your files that you want to read using HTCondor at T2_BR_UERJ have to be located at */mnt/hadoop/cms/store/user/*
(I'll say only *hadoop* for now on).

2. The files that you use to analyze/process the files that you are going to read don't need to be located at *hadoop*.
I highly recommend you to keep these files at your */home* folder, because is not so simple to manage files in *hadoop*.

3. I have made all *hadoop* management using *xrd* commands, for example : 

```
xrdfs xrootd.hepgrid.uerj.br rm /cms/store/user/(username)/(file)
```

```
xrdfs xrootd.hepgrid.uerj.br mkdir /cms/store/user/(username)/(directory)
```

```
xrdfs xrootd.hepgrid.uerj.br rmdir /cms/store/user/(username)/(directory)
```

```
xrdcp /home/.../(file) root://xrootd.hepgrid.uerj.br//cms/store/user/(username)/(file)
```

So, summarizing, put ntuples, samples, files you want to read at *hadoop* and files you want to execute at */home*.

## Files and commands explanation

### Executable file 

The executable file is where you want to describe what the HTCondor have to do when you runs it. For the example, my 
*sub_MC.sh* file :

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

1. **#!/bin/bash** : The shebang is a directive to the loader to use the program which is specified after the #! as the 
interpreter for the file in question when you try to execute it.

2. **file=$1** : This line is going to take the arguments from your file that have the list of files you want to read.

3. **echo "..."** : Just a command to return me which stage of the executable the HTCondor are in.

4. **ls -la $file**, **ls -la**, **pwd** : Just to confirm that I'm doing everything on the way that I want.

5. **root -b -l <<EOS ... EOS** : That is what I want the HTCondor to do for me. Just for a better understading, 
I open the root client, load my analyzer (that can be located at your */home* folder) and use this run function, 
where the first "" is the file I want to read (that have to be located at *hadoop*) and the second "" is the output file (that can be located at your */home*). Putting that way, the output files are going to appear in my *condor* folder, at */home*.

### Submission file

The submission file is where you are going to set up the HTCondor the way you want. For the example, my *condor_MC* file: 

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

1. **executable = sub_MC.sh** : Indicates to the executable you want to run using HTCondor.

2. **Universe = grid** : Set the HTCondor's universe (it is like the HTCondor's work environment) to grid (default is vanilla).

3. **output = test_MC/output_$(ProcId).out** : Saves the output text from the execution of the executable file. 
The $(ProcId) is to save the file with the number of the job that corresponds to that file.

4. **error = test_MC/output_$(ProcId).err** : Saves the error text from the execution of the executable file if it fails.

5. **log = test_MC/output_$(ProcId).log** : Saves the log text from the execution.

6. **getenv = True** : Gets the environment of the actual system and uses it on HTCondor's run. That is why you don't need to
do *cmsenv* on the executable file. With that said, obviously you need to run *cmsenv* on Analysis BEFORE running HTCondor.

7. **should_transfer_files = YES** : Explicitly enables the file transfer mechanism.

8. **when_to_transfer_output = ON_EXIT_OR_EVICT** : Tells HTCondor when output files are to be transferred back to the submit machine. For more information about options on 7 or 8 commands, visit https://research.cs.wisc.edu/htcondor/manual/v7.6/2_5Submitting_Job.html.

9. **transfer_input_files = ...** : Takes the selected files and transfer to where HTCondor is going to run.

10. **x509userproxy = /tmp/...** : Run in Analysis *id (username)* and copy the *uid* field. Complete *x509userproxy = /tmp/x509up_u(uid)*. Obviously you need to run *voms-proxy-init --voms cms* to use HTCondor.

11. **use_x509userproxy = true** : Explicitly asks for the voms-proxy generated file.

12. **+JobFlavour = "microcentury"** : Set the aproximate timestamp that you want to HTCondor to run your jobs. The longer 
the chosen time, the lower the job priority on server. But, if you put an insufficient timestamp, HTCondor will not end 
your job properly. More timestamps at https://twiki.cern.ch/twiki/bin/view/ABPComputing/LxbatchHTCondor.

13. **grid_resource = condor osgce2.hepgrid.uerj.br osgce2.hepgrid.uerj.br:9619** : Specifies the remote *condor_schedd* daemon to which the job should be submitted. More information at https://research.cs.wisc.edu/htcondor/manual/v7.6/5_3Grid_Universe.html.

14. **all +remote_...** : The remote machine needs to understand the attributes of the job. These are specified in the submit description file using the '+' syntax, followed by the string *remote_*.

15. **accounting_group...** : Individual settings for the one using Analysis.

16. **queue arguments from ListOfFiles_MC.txt** : Takes the arguments from *ListOfFiles_MC.txt*, my file that lists my files that 
are going to be read.

### List of files

The list of files is just an ordinary file that have all your files to be read. For the example, my *ListOfFiles_MC.txt* file : 


```
output_elastic_xangle100.root 
output_elastic_xangle110.root 
output_elastic_xangle120.root 
output_elastic_xangle130.root 
output_elastic_xangle140.root 
output_elastic_xangle150.root 
output_inel-el_xangle100.root 
output_inel-el_xangle110.root 
output_inel-el_xangle120.root 
output_inel-el_xangle130.root 
output_inel-el_xangle140.root 
output_inel-el_xangle150.root 

```

## Running HTCondor 

Still using my files as examples, we have :

```
condor_submit condor_MC
```

Submit your jobs.

```
condor_q
```

Check all jobs's status.

```
condor_rm (username) or condor_rm (jobid)
```

Remove all jobs or remove just selected jobs.


**If you have any questions, feel free to talk to me anytime**
