#Pipelines on the Epiphany
In the previous tutorial (available [here](tutorial3.md)) we looked at splitting a problem up geometrically. Driven by the decomposition of the data, different parts of the problem ran on different Epiphany cores with these cores often needing to communuicate when a neighbouring value held on another core was required. 

Whilst geometric decomposition is a very common approach, not all problems are suited to being split around the geometry of the data and instead this tutorial we will look at splitting up a problem based upon the flow of data, known as a pipeline, 

Before going any further, if you have not yet used or installed ePython then it is worth following the first tutorial ([here](tutorial1.md)) which walks you though installing ePython and running a simple "hello world" example on the Epiphany cores. If you installed ePython a while ago then it is worth ensuring that you are running the latest version, instructions for upgrading are available [here](installupgrade.md)

###Pipeline
A core represents a stage of a pipeline and here data flows into the first stage, some processing is performed on it and a resulting value flows into the next stage, which performs processing and passes it onto the next stage etc.. Once data has been sent from one stage to the next then that stage is ready to receive some more data and start processing that. 
<img src="https://raw.githubusercontent.com/mesham/epython/master/docs/pipeline.jpg">

This is illustrated in the diagram, in a pipeline data only flows one way (here from left to right) and at each stage the data is refined, from its initial "raw" value to the final "finished" value. Ideally you want all stages in the pipeline to be busy, when your program starts it takes some time to fill up the pipeline and at the end the pipeline drains.

###ePython pipeline
