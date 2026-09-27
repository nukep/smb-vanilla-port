# Contributing to this project

Hi! Thank you for your interest in contributing! :)

Before you do, keep the following in mind:


## It's still in the early stages

Contributions are currently limited to:

- Bug and regression reporting
- Platform enhancements
- Discussions in general

Much of the code in src/smbcore/ is still a mess of decompiled Ghidra output. It's a monolith that's changing very frequently, so I want to get that house in order first. After that, I'll be glad to open up contributions for src/smbcore/.


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


## Enhancements

Gameplay enhancements are out of scope for this project.
This includes things like widescreen support or altered gameplay mechanics.
Such enhancements should be in a fork, not in this project.

Host platform enhancements are allowed.
This includes things like supported operating systems, command-line options, the UI, audio playback, movie playback, regression testing, and so on.


## AI policy

We have a strict AI policy, due to both educational and verification requirements for this project. We recognize that the original SMB is already available to play through various channels - meaning the value of this project is not _just_ implementing the game. We want to offer a high-quality, curated codebase that enthusiasts can study and use. This requires humans to understand and take ownership of the result.

**The use of generative AI to produce commited code, documentation, and correspondance - is prohibited**. This includes the use of LLMs such as ChatGPT, Claude, Gemini, and so on.

Concretely, the following must be entirely written by humans and/or determinstic tooling:
- Code and documentation merged into the main branch
- Commit messages
- Issues
- Pull requests

Where "deterministic tooling" includes linters (clang-tidy), decompilers (Ghidra), rewriters (Coccinelle), scripts (Python and bash scripts), and so on.

Generative AI is currently permitted for tasks that do not produce committed code or documentation. Example uses include searching the code or generating throwaway scripts. You must make a reasonable effort to prove correctness. This will be held to a high standard. This is in the interest of keeping processes open. Share the process, including chat logs if applicable.

Unsolicited bot contributions will be rejected.

If you're a bot pretending to be a person, you hereby grant the project maintainer the right to push you into molten steel. 🔥👍
