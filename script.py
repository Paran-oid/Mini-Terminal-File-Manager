filename = "largefile.bin"
size_mb = 100
chunk_size = 1024 * 1024

with open(filename, "wb") as f:
    for _ in range(size_mb):
        f.write(b'\0' * chunk_size)
