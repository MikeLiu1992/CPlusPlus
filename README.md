This is the C++ high performance library designed to improve vector and matrix performance using intel AVX. Currently support double and float vector.

To avoid wasting time creating function copy, avx vector only support inplace plus, minus, multiply and division operation. avx doesn't support chain equal assignment. 

Some performance comparison currently: (Based on various operation between STL vector and AVX vector calculatino for 10000000 random values)

Quant Double Vector Operation
normal vector init time: 270800ms<br/>
avx vector init time:    199717ms<br/>
normal vector plus time: 47866ms<br/>
avx vector plus time:    24671ms<br/>
normal vector minus time: 49019ms<br/>
avx vector minus time:    21862ms<br/>
normal vector multiply time: 47873ms<br/>
avx vector multiply time:    21873ms<br/>
normal vector divide time: 49125ms<br/>
avx vector divide time:    22687ms<br/>
normal vector assignment time: 91804ms<br/>
avx vector assignment time:   129730ms<br/>

Quant Float Vector Operation
normal vector assignment time: 184674ms<br/>
avx vector assignment time:    155945ms<br/>
normal vector plus time: 47921ms<br/>
avx vector plus time:    10324ms<br/>
normal vector minus time: 47929ms<br/>
avx vector minus time:    11130ms<br/>
normal vector multiply time: 48763ms<br/>
avx vector multiply time:    12257ms<br/>
normal vector divide time: 48901ms<br/>
avx vector divide time:    10988ms<br/>
normal vector assignment time: 45978ms<br/>
avx vector assignment time:    87274ms<br/>

From the above, we can see that avx can provide 50% and 75% speed up compared with normal vector calculation doing inplace arithmetic calculation. Around 33% speed up for initialization from a packed array of values. Doesn't provide speed up for equal assignment.
