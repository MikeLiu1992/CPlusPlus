This is the C++ high performance library designed to improve vector and matrix performance using intel AVX. Currently support double and float vector.

To avoid wasting time creating function copy, avx vector only support inplace plus, minus, multiply and division operation. avx doesn't support chain equal assignment. 

Some performance comparison currently: (Based on various operation between STL vector and AVX vector calculatino for 10000000 random values)

Quant Double Vector Operation
normal vector init time: 270800ms
avx vector init time:    199717ms
normal vector plus time: 47866ms
avx vector plus time:    24671ms
normal vector minus time: 49019ms
avx vector minus time:    21862ms
normal vector multiply time: 47873ms
avx vector multiply time:    21873ms
normal vector divide time: 49125ms
avx vector divide time:    22687ms
normal vector assignment time: 91804ms
avx vector assignment time:   129730ms

Quant Float Vector Operation
normal vector assignment time: 184674ms
avx vector assignment time:    155945ms
normal vector plus time: 47921ms
avx vector plus time:    10324ms
normal vector minus time: 47929ms
avx vector minus time:    11130ms
normal vector multiply time: 48763ms
avx vector multiply time:    12257ms
normal vector divide time: 48901ms
avx vector divide time:    10988ms
normal vector assignment time: 45978ms
avx vector assignment time:    87274ms

From the above, we can see that avx can provide 50% and 75% speed up compared with normal vector calculation doing inplace arithmetic calculation. Around 33% speed up for initialization from a packed array of values. Doesn't provide speed up for equal assignment.