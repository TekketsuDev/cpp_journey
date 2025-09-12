---
tags:
  - firewall
  - hyper-v
  - wsl
Owner: Victor Jamet Soler
Status: in progress
---

# Additional Info


- [NetSecurity Module | Microsoft Learn](https://learn.microsoft.com/en-us/powershell/module/netsecurity/?view=windowsserver2025-ps)
- [Disable-NetFirewallHyperVRule (NetSecurity) | Microsoft Learn](https://learn.microsoft.com/en-us/powershell/module/netsecurity/disable-netfirewallhypervrule?view=windowsserver2025-ps#syntax)
## Get All Rules Displayed

``` powershell
	Get-NetFirewallRule -DisplayGroup "Hyper-V"
	
	# Export Same Info in csv
	Get-NetFirewallRule -DisplayGroup "Hyper-V" |  Select-Object * |  Export-Csv -Path "$env:USERPROFILE\Desktop\HyperV_FirewallRules.csv" -NoTypeInformation -Encoding UTF8 -Delimiter ";"
	
```

| Name                              | DisplayName                      | DisplayGroup | Enabled | Profile | Direction | Action | RemoteDynamicKeywordAddresses |
| --------------------------------- | -------------------------------- | ------------ | ------- | ------- | --------- | ------ | ----------------------------- |
| VIRT-WMI-WINMGMT-In-TCP-NoScope   | Hyper-V - WMI (TCP de entrada)   | Hyper-V      | True    | Any     | Inbound   | Allow  | {}                            |
| VIRT-WMI-ASYNC-In-TCP-NoScope     | Hyper-V - WMI (Async de entrada) | Hyper-V      | True    | Any     | Inbound   | Allow  | {}                            |
| VIRT-REMOTEDESKTOP-In-TCP-NoScope | Hyper-V (REMOTE_DESKTOP_TCP_IN)  | Hyper-V      | True    | Any     | Inbound   | Allow  | {}                            |
| VIRT-WMI-WINMGMT-Out-TCP-NoScope  | Hyper-V - WMI (TCP de salida)    | Hyper-V      | True    | Any     | Inbound   | Allow  | {}                            |
| VIRT-MIGL-In-TCP-NoScope          | Hyper-V (MIG-TCP de entrada)     | Hyper-V      | True    | Any     | Inbound   | Allow  | {}                            |
| VIRT-WMI-RPCSS-In-TCP-NoScope     | Hyper-V - WMI (DCOM de entrada)  | Hyper-V      | True    | Any     | Inbound   | Allow  | {}                            |
| VIRT-VMMS-RPC-EPMAP-In-NoScope    | Hyper-V (RPC-EPMAP)              | Hyper-V      | True    | Any     | Inbound   | Allow  | {}                            |
| VIRT-VMMS-RPC-In-NoScope          | Hyper-V (RPC)                    | Hyper-V      | True    | Any     | Inbound   | Allow  | {}                            |

---

