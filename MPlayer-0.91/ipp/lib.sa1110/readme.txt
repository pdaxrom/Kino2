Intel(R) Integrated Performance Primitives Version 1.11
      for the Intel(R) StrongARM* SA-1110 Microprocessor  

readme.txt 


/***********************************************************
Readme for Intel(R) Integrated Performance Primitives 
Version 1.11 for the Intel(R) SA-1110 Microprocessor 
(Linux version)
 

08/03/2001
***********************************************************/

Table of Contents

 Description .............................................2
 Features of Intel(R) IPP ................................2
 Kit Contents ............................................3
 Requirements ............................................4
 Installation ............................................4
 Known Problems ..........................................5
 Changes since Last Release ..............................5
 Related Documents .......................................6
 License Definitions .....................................6




































Description

This package contains the Intel(R) Integrated Performance Primitives (IPP) 
version 1.11 for the Intel(R) StrongARM* SA-1110 Microprocessor. This 
release version includes the following:

    - Part I Signal processing - Signal processing primitives
    - Part II Video codec - H.263 and MPEG-4 video decoder primitives
    - Part III Audio codec - MP3 audio decoder primitives
    - Part IV Image codec - JPEG image codec primitives 
    - Part V Speech codec - GSM-AMR and G.723.1 speech codec primitives 
    - Part VI Image processing - Image processing primitives 

Intel IPP release v1.11 builds on the v1.1 release by adding  new primitives 
to the existing audio codec primitives which enable developers to use the 
audio MP3 decoder primitives with user specified scalefactor band tables.
See "Changes since Last Release" for details.

The Intel(R) IPP has been developed under the following environment: 

   - Development Tool - GNU Cross-platform Tool Chain ('arm-linux'
     targeted) binutils-2.10-1 and gcc-2.95.2-2.
   - Processor - Intel(R) StrongARM* SA-1110 Microprocessor.
   - Reference board - Intel(R) StrongARM* SA-1110 Evaluation Board.
   - Operating system - Linux 2.4.0-test5-rmk1-np1.

The software is targeted at the above environment; however, efforts have been
made to keep the software in the ANSI C style whenever possible. Although 
Intel(R) IPP functions have been tested, no warranty, expressed or implied is
to be associated with these functions as well as all the associated materials
in this package. All risk assumed is by the user. See the License Agreement for
details.

-------------------------------------------------------------------------------

Features of Intel(R) IPP

Intel(R) IPP version 1.11 is organized into following six parts: 
    

Part I Signal processing primitives contain: 
    
    - General arithmetic operations
    - Filtering
    - Convolution
    - Transform
    - Sample generation
    - Windowing

Part II Video codecs - H.263 and MPEG-4 video decoder primitives contain:
    
    - Variable length decoding (VLD) and inverse zigzag positioning
    - Inverse quantization
    - Inverse discrete cosine transforms (IDCT)
    - Motion vector decoding
    - Padding and compensation
    - Overlapped block motion compensation (OBMC)
    - Coefficient prediction
    - Block based decoding
    - Deblocking filtering

Part III Audio codec - MP3 decoder primitives contain:
    
    - Frame unpacking operations
    - Huffman decoding
    - Requantization module
    - Inverse Modified Discrete Cosine Transform (IMDCT) filterbank
    - Pseudo Quadrature Mirror Filterbank (PQMF)

Part IV Image codec - JPEG image codec primitives contain:

    - Color conversion
    - Discrete Cosine Transform (DCT)/Quantization and IDCT/Dequantization
    - Huffman encoding and decoding
    - Baseline sequential DCT-based encoding and decoding
    - Progressive DCT-based encoding and decoding

Part V Speech codecs - GSM-AMR and G.723.1 speech codec primitives contain:

    - Linear Prediction (LP) analysis
    - Adaptive-codebook search
    - Fixed-codebook search
    - Discontinuous transmission
    - Filtering
    - Post-filtering

Part VI Image processing primitives contain:

    - General Arithmetic and Logical Operations
    - Filtering
    - Linear Transforms
    - Color Space Conversion
    - Morphological Operations
    - Statistics 

-------------------------------------------------------------------------------

Kit Contents

Intel(R) IPP V1.11 for Intel(R) StrongARM* SA-1110 Microprocessor package
contains separate binary library files with corresponding header files, global   
header files, and support documents. Users have the option to install all of
the binary library files or any that they choose with the global header 
files. Each binary library has a release version and debug version. In the 
debug version, the functions check the input arguments and provide error 
messages when improperly used. In the release version, input arguments will 
not be checked, and improper usage will result in unpredictable behavior. 

Global header files: 
    - ipp.h 
    - ippdefs.h 
 
Library components with the corresponding header files:

    - ippSP_SA111LNX_r.a: release version of signal processing binary library
      file 
    - ippSP_SA111LNX_d.a: debug version of signal processing binary library
      file 
    - ippSP.h: header file for the signal processing domain. This header file 
      contains the "C" prototype for the every primitive in this domain and  
      associated structures, constants, etc.

    - ippVC_SA111LNX_r.a: release version of video codec binary library file
    - ippVC_SA111LNX_d.a: debug version of video codec binary library file 
    - ippVC.h: header file for the video codec domain. This header file contains  
      the "C" prototype for the every primitive in this domain and associated  
      structures, constants, etc.

    - ippAC_SA111LNX_r.a: release version of audio codec binary library file  
    - ippAC_SA111LNX_d.a: debug version of audio codec domain
    - ippAC.h: header file for the audio codec domain. This header file contains  
      the "C" prototype for the every primitive in this domain and associated  
      structures, constants, etc.

    - ippJP_SA111LNX_r.a: release version of Jpeg codec binary library file  
    - ippJP_SA111LNX_d.a: debug version of audio codec domain
    - ippJP.h: header file for the audio codec domain . This header file contains  
      the "C" prototype for the every primitive in this domain and associated  
      structures, constants, etc.   

    - ippSC_SA111LNX_r.a: release version of speech codec binary library file  
    - ippSC_SA111LNX_d.a: debug version of speech codec domain
    - ippSC.h: header file for the speech codec domain. This header file contains  
      the "C" prototype for the every primitive in this domain and associated  
      structures, constants, etc.

    - ippIP_SA111LNX_r.a: release version of image processing binary library file
    - ippIP_SA111LNX_d.a: debug version of image processing binary library file 
    - ippIP.h: header file for the image processing domain. This header file  
      contains the "C" prototype for the every primitive in this domain and  
      associated structures, constants, etc.

The support documents: 
    - license.txt: License definitions
    - readme.txt (this file)

-------------------------------------------------------------------------------

Requirements

Intel(R) IPP for the Intel(R) StrongARM* SA-1110 Microprocessor requires: 

    - Host machine: An Intel(R) Pentium(R) II 450MHz processor based PC with 64MB 
      RAM, or better 
    - Operating system: Red Hat Linux Release 6.2  
    - Development tool: GNU Cross-platform Tool Chain ('arm-linux'targeted) 
      binutils-2.10-1 and gcc-2.95.2-2, Red Hat RPM version 3.0.4
    - Target platform: Intel(R) StrongARM* SA-1110 Evaluation Board
     
-------------------------------------------------------------------------------

Installation

You can install the Intel(R) IPP by downloading installation file ippsa111_lnx.rpm 
from the Intel(R) developer web site. Please follow the download instructions 
on the Web site. 

To install this package, login as super-user and enter the following command:

rpm -i ippsa111_lnx.rpm 

Type rpm -help for more options.

To integrate Intel(R) IPP into your development environment, the *.h and *.a 
files should be included in your search path.

After installation, the following files reside in these directories: 

    usr/local/ipp/ippsa111: main directory
        readme.txt - brief overview, this file
        license.txt - license agreement document
 
    usr/local/ipp/ippsa111/include: Directory for C "include" files
        ipp.h - master Intel(R) IPP include file
        ippdefs.h - master Intel(R) IPP definition include file
        ipp*.h - include files for each domain accessed through ipp.h
 
    usr/local/ipp/ippsa111/lib: directory for binary library components
        *.a - chosen static library files
        

-------------------------------------------------------------------------------

Known Problems

None known at the time of the printing of this document. 

-------------------------------------------------------------------------------

Changes Since Last Release

 
Software Changes:


	Users of Intel(R) IPP version 1.1 for Intel(R) StrongARM* SA-1110 Microprocessor 
	should note that the following new functions are available in this release.

      Audio codec - the following primitives are added in the audio codec:
        IppStatus ippsHuffmanDecodeSfb_MP3_1u32s()
        IppStatus ippsReQuantizeSfb_MP3_32s_I()

	Users of Intel(R) IPP version 1.01 for Intel(R) StrongARM* SA-1110 Microprocessor 
	should note that the following new features/functions are available in this release.


    - New features: Users of Intel(R) IPP version 1.01 for Intel(R) StrongARM*  
      SA-1110 Microprocessor should note that the following two new features are  
      available in this release.

      Speech Codec: Speech codec includes GSM-AMR and G.723.1 primitives. 
      Image Codec: Image codec includes JPEG primitives. 

    - New primitives: Users of Intel(R) IPP version 1.01 for Intel(R) StrongARM*  
      SA-1110 Microprocessor should also note that the following new primitives  
      are available in this release.
    
      Signal processing - the following primitives are added:
        IppStatus ippsFFTFwd_CToCL32_32sc();
        IppStatus ippsFFTFwd_CToCL64_32sc();
        IppStatus ippsFFTFwd_CToCL128_32sc();
        IppStatus ippsFFTFwd_CToCL256_32sc();
        IppStatus ippsFFTFwd_CToCL512_32sc();
        IppStatus ippsFFTFwd_CToCL1024_32sc();
        IppStatus ippsFFTInv_CToCL32_32sc();
        IppStatus ippsFFTInv_CToCL64_32sc();
        IppStatus ippsFFTInv_CToCL128_32sc();
        IppStatus ippsFFTInv_CToCL256_32sc();
        IppStatus ippsFFTInv_CToCL512_32sc();
        IppStatus ippsFFTInv_CToCL1024_32sc();
      Image processing - the following primitives are added:
        IppStatus ippiYUV420ToRGB555_8u16u_P3C3R()
        IppStatus ippiYUV420ToRGB565_8u16u_P3C3R()
        IppStatus ippiYUV420ToRGB444_8u16u_P3C3R()
        IppStatus ippiYUV420ToBGR555_8u16u_P3C3R()
        IppStatus ippiYUV420ToBGR565_8u16u_P3C3R()
        IppStatus ippiYUV420ToBGR444_8u16u_P3C3R()
      Audio codec - the following primitives are added:
        IppStatus ippsHuffmanDecodeSfb_MP3_1u32s()
        IppStatus ippsReQuantizeSfb_MP3_32s_I()


Documentation Changes:

  The following changes are made to the Intel(R) Integrated Performance 
  Primitives for the Intel(R) StrongARM* SA-1110 Microprocessor Reference manual, 
  v1.1 and v1.01 (order numbers 278288005 and 278288004 respectively).
  For IPP v1.01 users
   - Two new chapters titled "JPEG codec" and "Speech Codec" are added. These 
     two chapters detail the usage of the primitives of the two new  
     features/domains added in this release correspondingly.   
   - Descriptions for the new primitives are added in signal procesing, image 
     processing, and audio codec chapters for the new primitives listed in the 
     software changes section.
  For IPP v1.1 users
   - Descriptions for the new primitives are added in audio codec chapter for the 
     new primitives listed in the software changes section.
-------------------------------------------------------------------------------

Related documents 

1) Intel(R) Integrated Performance Primitives for the Intel(R) StrongARM* 
   SA-1110 Microprocessor Reference Manual, Version 1.11 (278288006.pdf).  

2) Other documents that may be helpful while reading this document are listed 
   in the reference section of the Intel(R) Integrated Performance Primitives
   Reference Manual (278288006.pdf).

-------------------------------------------------------------------------------

License Definitions

Please refer to the Intel(R) Integrated Performance Primitives license file for
the license agreement details.

-------------------------------------------------------------------------------

Information in this document is provided in connection with Intel(R) products.
No license, express or implied, by estoppel or otherwise, to any intellectual
property rights is granted by this document. Except as provided in Intel's 
Terms and Conditions of Sale for such products, Intel assumes no liability 
whatsoever, and Intel disclaims any express or implied warranty, relating to
sale and/or use of Intel products including liability or warranties relating
to fitness for a particular purpose, merchantability, or infringement of any 
patent, copyright or other intellectual property right. Intel products are not
intended for use in medical, life saving, or life sustaining applications. 

Intel may make changes to specifications and product descriptions at any time,
without notice.

Designers must not rely on the absence or characteristics of any features or 
instructions marked "reserved" or "undefined." Intel reserves these for future 
definition and shall have no responsibility whatsoever for conflicts or 
incompatibilities arising from future changes to them.

The Intel(R) StrongARM* SA-1110 Evaluation Platform Board Manual may contain  
design defects or errors known as errata which may cause the product to deviate 
from published specifications. Current characterized errata are available on 
request.

MPEG-4, H.263, MP3, JPEG, GSM-AMR and G.723.1 are international standards 
promoted by ISO, ITU, ETSI and other organizations. Implementations of these 
standards, or the standard enabled platforms may require licenses from various 
entities, including Intel Corporation.

Contact your local Intel sales office or your distributor to obtain the latest
specifications and before placing your product order.

Copies of documents which have ordering numbers and are referenced in this 
document, or other Intel literature may be obtained by calling 1-800-548-4725
or by visiting Intel's website at http://www.intel.com.

Copyright (c) Intel Corporation, 2001

Intel is a trademark or registered trademark of Intel Corporation or its 
subsidiaries in the United States and other countries.
* Other brands and names are the property of their respective owners.




