# Optimization Notes

## Mem2Reg
- alloca 但没用过的不alloca
- 只被定义了一次，那么所有值都可以用定义的值代替
- 如果一个alloca 只在当前块被使用，那么所有的use都可以被向上最近的一个def替代