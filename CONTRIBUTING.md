# Contributing to this project

Hi! Thank you for your interest in contributing! :)

Before you do, keep the following in mind:


## Bugs

A bug is defined as:

- Gameplay behavior that's not in the original SMB1 or SMB2J
- An issue with the host platform (e.g. issues running on Windows/Linux, SDL, movie playback, etc)

If you believe you've encountered one, feel free to create an issue or pull request if it doesn't exist yet.


## Backwards compatibility

It's important to behave as identically to the original unmodified games as is practical, including glitches.

If there's a glitch that got missed, then it's probably a bug.

Keep in mind however, that 100% backwards compatibility is not possible.
Details such as the stack, and temporary $00-$08 registers, are abstracted away for simplicity.
There may be rare glitches in the original games that depend on these details.

We should probably document all non-implementable glitches though, so feel free to create an issue regardless.


## Regression testing

TODO: Expand on this section.

Right now, contributers are NOT expected to perform regression testing. This will change in the future.
All changes will be regression-tested by the maintainer.

This project builds a `smbvanilla_testrunner` executable. As of writing, the project maintainer has a bespoke setup for this, so it's not fully documented yet. He currently validates by testing against several TAS and non-TAS gameplays. Movies (per-frame button and RAM dumps) are created with FCEUX using the `fceux_movie_dump.lua` script. The movie files are rather large, so they're not committed to this repo.


## Refactoring

Refactoring or simplifying code is encouraged, within reason.

Examples of acceptable refactors:

- Simplifying loops
- Inlining trivial subroutines
- Creating or renaming constants
- Using 16-bit arithmetic helpers
- Reordering non-aliased variable assignments
- Assuming invariants (e.g. if a subroutine sets a constant, and the caller uses it)
- Removing unreachable code/branches

We want the code for this project to be a good cross-reference for existing disassemblies.
In particular, doppelganger's disassemblies of SMB1 and SMB2J.
This is for both practical and educational reasons. Fixing issues is easier if it can be cross-referenced. An enthusiast who wishes to study SMB's original 6502 may find the higher-level code useful.

If a refactor potentially obscures a relevant low-level detail, comments are encouraged.

Example comments:

- `Inlined: Foo`
- `Note: There's a carry bug here. "ADC Bar" was used without "CLC".`.
- `Note: Foo() always sets the "A" register to 0. Setting Bar to 0 because of the "STA Bar" 6502 instruction.`


## Enhancements

Gameplay enhancements are out of scope for this project.
This includes things like widescreen support or altered gameplay mechanics.
Such enhancements should be in a fork, not in this project.

Host platform enhancements are allowed.
This includes things like supported operating systems, command-line options, the UI, audio playback, movie playback, regression testing, and so on.


## AI policy

We have a strict AI policy, due to the verification requirements for this project.

The use of LLM output as commited code or documentation, is prohibited.

All contributor correspondance (e.g. issues, pull requests) must be written by a person.

LLMs are allowed for assistive tasks that do not directly produce committed code or documentation, but it must be disclosed for transparency. You must make a reasonable effort to prove correctness. This will be held to a high standard.
This is in the interest of keeping processes open. Share chat logs/prompts if applicable.

The bottom line: Verification is important for this project, and must involve humans and deterministic tooling.

Unsolicited bot contributions will be rejected.

If you're a bot pretending to be a person, you hereby grant the project maintainer the right to push you into molten steel. 🔥👍
