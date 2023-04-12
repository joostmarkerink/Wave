# Wave
a cpp object to easily generate an audio wave.

call the "update" method at the end of every frame, after you extract the wave using "get".
Set the "shape" property to Wave::TRIANGLE, Wave::SAWTOOTH, Wave::SQUARE or Wave::TABLE.
Only set "shape" to Wave::TABLE after you set a table "setTable(myvalues,numofvalues)".
