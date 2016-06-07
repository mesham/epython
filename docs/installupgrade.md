#Installing ePython

To install ePython you need to checkout a version from the repository, build it and then install it. Firstly, log into your Parallella and issue

```
git clone https://github.com/mesham/epython.git
```

copy ePython onto your machine and a directory called *epython* will have been created. Next we are going to build this by issuing the make command, from the top level directory (the one you issued the git clone into) issue the following two commands:

```
cd epython
make
```

The build process takes around 20-30 seconds and once complete you will be returned to the bash prompt. The next (and last) step is to install ePython to a central location by issuing the two commands below. You will be promoted for your user's password with the first command. The second command (bash) starts a new bash terminal which has the python paths correctly set and every time bash starts from now on it will be correctly configured for ePython.

```
sudo make install
bash
```

Congratulations! You have installed ePython and are ready to start programming! 

#Upgrading ePython

ePython is actively being developed, so new features and bug fixes are being added to the code. Because of this, and to ensure you can run the latest examples, it is useful to periodically ensure you have the latest ePython and if not upgrade your version. The process is similar to the installation process, ensure you are in the *epython* directory (you might need to issue *cd epython*) and then issue:

```
git pull
```

This will contact the ePython repository and download any updates. If you see the message *Already up-to-date.* then you already have the latest version and can stop here, if not then you have downloaded some updates and we need to build and install these via:

```
make
sudo make install
```

This will replace the older version of ePython with this latest, newer version. It is just the ePython interpreter that is being updated, so don't worry - all your own Python codes will remain unchanged and untouched by this.
