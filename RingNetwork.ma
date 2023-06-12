[Top]
components : NodeA@RingNode NodeB@RingNode NodeC@RingNode NodeD@RingNode NodeE@RingNode NodeF@RingNode NodeG@RingNode NodeH@RingNode 
out : outLeader 
in : wakeUpA wakeUpB wakeUpC wakeUpD wakeUpE wakeUpF wakeUpG wakeUpH 
Link : wakeUpA wakeUp@NodeA
Link : wakeUpB wakeUp@NodeB
Link : wakeUpC wakeUp@NodeC
Link : wakeUpD wakeUp@NodeD
Link : wakeUpE wakeUp@NodeE
Link : wakeUpF wakeUp@NodeF
Link : wakeUpG wakeUp@NodeG
Link : wakeUpH wakeUp@NodeH
Link : outR@NodeA inL@NodeB
Link : outL@NodeB inR@NodeA
Link : outR@NodeB inL@NodeC
Link : outL@NodeC inR@NodeB
Link : outR@NodeC inL@NodeD
Link : outL@NodeD inR@NodeC
Link : outR@NodeD inL@NodeE
Link : outL@NodeE inR@NodeD
Link : outR@NodeE inL@NodeF
Link : outL@NodeF inR@NodeE
Link : outR@NodeF inL@NodeG
Link : outL@NodeG inR@NodeF
Link : outR@NodeG inL@NodeH
Link : outL@NodeH inR@NodeG
Link : outR@NodeH inL@NodeA
Link : outL@NodeA inR@NodeH
Link : outDone@NodeA outLeader
Link : outDone@NodeB outLeader
Link : outDone@NodeC outLeader
Link : outDone@NodeD outLeader
Link : outDone@NodeE outLeader
Link : outDone@NodeF outLeader
Link : outDone@NodeG outLeader
Link : outDone@NodeH outLeader

[NodeA]
id : 1

[NodeB]
id : 2

[NodeC]
id : 3

[NodeD]
id : 4

[NodeE]
id : 5

[NodeF]
id : 6

[NodeG]
id : 7

[NodeH]
id : 8


