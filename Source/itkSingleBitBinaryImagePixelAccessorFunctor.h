/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkSingleBitBinaryImagePixelAccessorFunctor.h,v $
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkSingleBitBinaryImagePixelAccessorFunctor_h
#define __itkSingleBitBinaryImagePixelAccessorFunctor_h

namespace itk
{
/** \class SingleBitBinaryImagePixelAccessorFunctor
 * \brief Provides accessor interfaces to Access pixels and is meant to be
 * used by iterators.
 *
 * A typical user should not need to use this class. The class is internally
 * used by the neighborhood iterators.
 *
 * The pixel accessor is set with the SetPixelAccessor method. This accessor is 
 * meant to be used only for SparseImage and not for Image.
 *
 * \author Dan Mueller, Philips Healthcare, PII Development
 *
 * This implementation was taken from the Insight Journal paper:
 * http://hdl.handle.net/10380/3068
 *
 */
template <class TImageType >
class ITK_EXPORT SingleBitBinaryImagePixelAccessorFunctor
{
public:

  typedef TImageType                                   ImageType;
  typedef typename ImageType::InternalPixelType        InternalPixelType;
  typedef typename ImageType::PixelType                ExternalPixelType;
  typedef typename ImageType::AccessorType             PixelAccessorType;
  typedef unsigned int                                 VectorLengthType;
  
  /** Set the PixelAccessor. This is set at construction time by the image iterators.
   * The type PixelAccessorType is obtained from the ImageType over which the iterators
   * are templated.
   * */
  inline void SetPixelAccessor( PixelAccessorType& accessor )
    {
    m_PixelAccessor = accessor;
    }

  /** Set the pointer index to the start of the buffer. */
  inline void SetBegin( const InternalPixelType * begin )
    { this->m_Begin = const_cast< InternalPixelType * >( begin ); }

  /** Set output using the value in input */
  inline void Set( InternalPixelType & output, const ExternalPixelType &input ) const
    {
    m_PixelAccessor.Set( output, input, (&output)-m_Begin );
    }

  /** Get the value from input */
  inline ExternalPixelType Get( const InternalPixelType &input ) const
    {
    return m_PixelAccessor.Get( input, (&input)-m_Begin );
    }

  /** Required for some filters to compile. */
  static void SetVectorLength( ImageType *, VectorLengthType )
    {
    }

  /** Required for some filters to compile. */
  static VectorLengthType GetVectorLength( const ImageType * )
    {
    return 1;
    }

private:
  PixelAccessorType m_PixelAccessor;
  InternalPixelType *m_Begin;
};

}

#endif
