# Command Faker
> An executable file generator that used to fake other programs.

<p>
  <a href="https://raw.githubusercontent.com/songquanpeng/command-faker/main/LICENSE">
    <img src="https://img.shields.io/github/license/songquanpeng/command-faker?color=brightgreen" alt="license">
  </a>
  <a href="https://github.com/songquanpeng/command-faker/releases/latest">
    <img src="https://img.shields.io/github/v/release/songquanpeng/command-faker?color=brightgreen&include_prereleases" alt="release">
  </a>
  <a href="https://github.com/songquanpeng/command-faker/releases/latest">
    <img src="https://img.shields.io/github/downloads/songquanpeng/command-faker/total?color=brightgreen&include_prereleases" alt="release">
  </a>
</p>

## Basic Usages
```shell
# Specify a output name:
ls | ./faker tmp && ./tmp
# If you don't, it will output to stdout.
ls | ./faker > tmp && chmod u+x ./tmp && ./tmp
```
