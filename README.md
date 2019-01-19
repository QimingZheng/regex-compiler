# regex-compiler

[English](README.md) [中文版](README-CN.md)

1. This repo is a part for my graduation project，about regex-match engine acceleration.

2. Directories src/ contains a series of tools: **parser**，**compiler**，**matcher**, and I'll keep enlarging supported grammar (till 2018.12.15，only basic operands: '|','.','*' are supported, alphabet: char，(unicode can be supported by reading 2-byte unicode as 2 continuous byte char)). This regex can only support **standard regular language**, actually, most modern regex-engine supports CFG grammar, even beyond CFG. Thus,modern regex (like perl，pcre etc.) is not standard regular language，regular language is a subset of the language they support. For more knowledge about automaton theory/computation langhage theory, please refer to related textbooks.

3. Why I don't support those non-standard grammars? Here is my statement:
    - As long as a grammar satisfies Regular Language rules, or it can be expressed as a grammar that equavalent to Regular Language grammar (by convertion), regex in this repo will support (now or in the next stage)，in the next steo，I'll build a set tools that support more commonly used RL grammars.
    - If a grammar is non-standard, like back-reference, I won't and cannot support them in the future.
    
        Reason:
        The main purpose of this project is exploring the possibility and utmost of accelerate match algorithm in GPU or other ASIC platforms.
        If I want to support those non-standard rules, I have to change the current runtime match algorithm (a highly paralleled and high efficient algorithm), and use dfs-like algorithm to do the match tasks, which is difficult for the parallelization and usually cache-unfriendly. At the same time, a very power regex library: hyperscan，does not support non-standard ones also.
        Certainly, I'm lazy doesn't mean there is no possibility of keep supporting those non-standard ones in the future, but matcher might need to be rewrite and maybe AST constructed by parser should be modified. If you have interests in this task, please go ahead! Contact me if you have doubts on my part😝

4. Algorithm and implementation details please refer to directory doc/

5. Another highly related project is multi-pattern-match engine. In practise, string-match can reduce regex-engine's load a lot, any filters other than string-match that can filter out impossible inputs can help improve regex-engine. From the point of decoupling engineering complexity, this repo only focus on improve regex-engine's performance.
