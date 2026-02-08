<div align = center>

<div style='margin-bottom: 30px; margin-top: 20px;'>
<img src='https://cdn.vobrow.com/W.png' style="width: 300px;">
</div>

<img src='https://img.shields.io/badge/Workflow-Wire-blue?style=for-the-badge&logo=git'>
<img src='https://img.shields.io/github/issues/wyrexdev/Wire?style=for-the-badge&logo=github'>
<img src='https://img.shields.io/github/issues-pr/wyrexdev/Wire?style=for-the-badge&logo=github'>
<img src='https://img.shields.io/github/languages/top/wyrexdev/Wire?style=for-the-badge'>
<img src='https://img.shields.io/github/license/wyrexdev/Wire?style=for-the-badge'>
<img src='https://img.shields.io/badge/discord-wyrex-red?style=for-the-badge&logo=discord'>

<div style="margin-top: 10px;">
<p style="font-family: 'Trebuchet MS', sans-serif;">
Wire is a low-level networking and protocol engine designed for speed, correctness, and full control over data flow.
</p>
</div>

--- 
</div>

<h2 style="font-family: 'Trebuchet MS', sans-serif;">Features</h2>
<div style="font-family: 'Trebuchet MS', sans-serif;">• Native HTTP/HTTPS implementation with manual request and response handling.</div>
<div style="font-family: 'Trebuchet MS', sans-serif;">• Full TLS stack integration without third-party HTTP clients.</div>
<div style="font-family: 'Trebuchet MS', sans-serif;">• Streaming support for large responses and chunked transfers.</div>
<div style="font-family: 'Trebuchet MS', sans-serif;">• Built-in decoding for modern content encodings (gzip).</div>
<div style="font-family: 'Trebuchet MS', sans-serif;">• Precise control over redirects, headers, and connection lifecycle.</div>
<div style="font-family: 'Trebuchet MS', sans-serif;">• Deterministic request behavior with zero hidden retries or heuristics.</div>
<div style="font-family: 'Trebuchet MS', sans-serif;">• Binary-safe pipeline designed for browsers, proxies, and tooling.</div>
<div style="font-family: 'Trebuchet MS', sans-serif;">• Modular architecture separating transport, protocol, and codec layers.</div>
<div style="font-family: 'Trebuchet MS', sans-serif;">• No telemetry, no background requests, no implicit network activity.</div>

---

<h2 style="font-family: 'Trebuchet MS', sans-serif;">Installation</h2>

<h3 style="font-family: 'Trebuchet MS', sans-serif;">1.1 - Required</h3>

<div style="font-family: 'Trebuchet MS', sans-serif;">• ZLib </div>

<h3 style="font-family: 'Trebuchet MS', sans-serif;">1.2 - ZLib Installation</h3>

```
sudo pacman -S zlib
```

---

<h3 style="font-family: 'Trebuchet MS', sans-serif;">1.4 - Git Clone</h3>

```
git clone https://github.com/wyrexdev/Wire.git
```

---

<h3 style="font-family: 'Trebuchet MS', sans-serif;">1.5 - Install Wire</h3>

```
sudo make install
```

---