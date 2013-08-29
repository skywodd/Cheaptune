import math

SAMPLES_PER_LINE = 10

# Generate the .inc file for the specified bit depth
def genSinusTable(bitsCount):

    # Debug message
    print "Generating sinus include file for bit depth %d" % bitsCount

    # Create output file
    fo = open("sinus_%db.inc" % bitsCount, 'w')
    if not fo:
        print "Cannot create output file sinus_%db.inc" % bitsCount
        exit(1)
    
    # Compute samples count
    samplesCount = (1 << bitsCount)

    # Compute each samples
    wrap = 0
    for i in xrange(0, samplesCount / 4, 1):

        # Compute float sample value
        sample = math.sin(2.0 * math.pi * (float(i) / samplesCount)) * 32767

        # Turn float into integer
        sample = int(sample)

        # Write value
        if wrap == SAMPLES_PER_LINE:
            fo.write("%d, \n" % sample)
            wrap = 0
        else:
            fo.write("%d, " % sample)
            wrap += 1

    # Close output file
    print "%d / %d samples generated" % ((samplesCount / 4), samplesCount)
    fo.close()

# Generate the .inc file for the specified bit depth
def genExpTable(bitsCount):

    # Debug message
    print "Generating exp include file for bit depth %d" % bitsCount

    # Create output file
    fo = open("exp_%db.inc" % bitsCount, 'w')
    if not fo:
        print "Cannot create output file sinus_%db.inc" % bitsCount
        exit(1)
    
    # Compute samples count
    samplesCount = (1 << bitsCount)

    # Compute each samples
    wrap = 0
    for i in xrange(0, samplesCount, 1):

        # Compute float sample value
        sample = (1.0 - math.exp(-i / (samplesCount / 5.0))) * 255

        # Turn float into integer
        sample = int(sample)

        # Write value
        if wrap == SAMPLES_PER_LINE:
            fo.write("%d, \n" % sample)
            wrap = 0
        else:
            fo.write("%d, " % sample)
            wrap += 1

    # Close output file
    print "%d samples generated" % samplesCount
    fo.close()

# Run generator
if __name__ == '__main__':

    # Generate sinus include files
    for i in range(9, 17, 1):
        genSinusTable(i)

    # Generate exp include files
    for i in range(9, 17, 1):
        genExpTable(i)
