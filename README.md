# Shaiya Episode 6

## Environment

Windows 10

Visual Studio 2022

C++ 23

## Prerequisites

[Microsoft Visual C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x86.exe)

## Development

The intent is to provide episode 6 client support. The best way to contribute is to report issues. Please don't send code because it's a pain in the ass to review, etc.

### Pull Requests

Pull requests are not welcome. GitHub doesn't allow the pull requests tab to be disabled.

### Issues

Send me an email.

## Injection

### Cheat Engine

Cheat Engine isn't guaranteed to work for everyone. I recommend using Cheat Engine 7.3 because users have reported issues with newer versions.

### Imports

The libraries have an export defined in the main headers. I recommend using [PE Bear](https://github.com/hasherezade/pe-bear) to add new imports.

## Data Execution Prevention (DEP)

Intermittent access violations have been reported on Windows Server 2022. The issue is related to [Data Execution Prevention](https://learn.microsoft.com/en-us/windows/win32/memory/data-execution-prevention). The following command will output the DEP support policy:

```
wmic OS Get DataExecutionPrevention_SupportPolicy
```

## False Positives

The files in this repository are submitted to antivirus companies for analysis when viruses are detected during VirusTotal scans, etc. VirusTotal provides a list of false positive [contacts](https://docs.virustotal.com/docs/false-positive-contacts).

## Inspiration

[Cups](https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/4653021-shaiya-library.html)

[EricDutra-16](https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/4189218-release-wip-ep6-source-code.html)

[shen1l](https://www.elitepvpers.com/forum/shaiya-pserver-guides-releases/3669922-release-ep6-itemmall-fixed.html)

## References

[Eden](https://github.com/tristonplummer/Eden)

[Teos](https://github.com/ShaiyaTeos/Teos)

[Parsec](https://github.com/matigramirez/Parsec)
