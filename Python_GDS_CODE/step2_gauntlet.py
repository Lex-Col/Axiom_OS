import gdstk

# 1. Start the Gauntlet Build
lib = gdstk.Library("AXIOM_GAUNTLET")
# Load the 9 Seal unit cell we already built
halo_cell = gdstk.read_gds("AXIOM_9_SEAL.gds").top_level()[0]
gauntlet = lib.new_cell("12_NODE_GAUNTLET")

print("[+] Initiating 12-Node Array...")

# 2. Layout the 12 Nodes (3x4 Grid)
# We space them at 500 units to allow room for the Isolation Trenches
for i in range(12):
    col = i % 4
    row = i // 4
    x, y = col * 500, row * 500
    
    # Place the logic node
    node_ref = gdstk.Reference(halo_cell, (x, y))
    gauntlet.add(node_ref)
    
    # 3. Add Deep-Trench Isolation (DTI) - From Axiom Spec 2.0
    # This is a 'dead zone' around every node so light can't leak out
    trench = gdstk.rectangle((x-50, y-50), (x+400, y+400), layer=2, datatype=0)
    gauntlet.add(trench)

# 4. Save the expanded Gauntlet
lib.write_gds("AXIOM_GAUNTLET_V1.gds")
print("[+] STEP 2 COMPLETE: 12-Node Gauntlet with DTI created.")
