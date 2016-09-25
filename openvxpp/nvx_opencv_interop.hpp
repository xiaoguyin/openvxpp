/*
* Copyright (c) 2014-2015, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA Corporation and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA Corporation is strictly prohibited.
*/

#ifndef __NVX_OPENCV_INTEROP_HPP__
#define __NVX_OPENCV_INTEROP_HPP__

#include <limits>

#include <NVX/nvx.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/cuda.hpp>

#ifndef __cplusplus
#   error nvx_opencv_interop.hpp header must be compiled as C++
#endif

#ifdef VISIONWORKS_7_5

/**
* \brief NVIDIA VisionWorks OpenCV Interoperability APIs.
*/
namespace nvx_cv {

	/**
	* \ingroup nvx_opencv_interop
	* \brief Converts from OpenVX Matrix' type to OpenCV Mat's type.
	*
	* \param [in] matrix_type  OpenVX Matrix' type.
	*
	* \return OpenCV Mat's type.
	*/
	inline int convertVXMatrixTypeToCVMatType(vx_enum matrix_type)
	{
		switch (matrix_type)
		{
		case VX_TYPE_UINT8:
			return CV_8UC1;
		case VX_TYPE_INT8:
			return CV_8SC1;
		case VX_TYPE_UINT16:
			return CV_16UC1;
		case VX_TYPE_INT16:
			return CV_16SC1;
		case VX_TYPE_UINT32:
		case VX_TYPE_INT32:
			return CV_32SC1;
		case VX_TYPE_FLOAT32:
			return CV_32FC1;
		case VX_TYPE_FLOAT64:
			return CV_64FC1;
		case NVX_TYPE_POINT2F:
			return CV_32FC2;
		case NVX_TYPE_POINT3F:
			return CV_32FC3;
		}
		CV_Error(CV_StsUnsupportedFormat, "Unsupported format");
		return 0;
	}

	/**
	* \ingroup nvx_opencv_interop
	* \brief Converts from OpenCV Mat's type to OpenVX Matrix' type.
	*
	* \param [in] mat_type     OpenCV Mat's type.
	*
	* \return OpenVX Matrix' type.
	*/
	inline vx_enum convertCVMatTypeToVXMatrixType(int mat_type)
	{
		switch (mat_type)
		{
		case CV_8UC1:
			return VX_TYPE_UINT8;
		case CV_8SC1:
			return VX_TYPE_INT8;
		case CV_16UC1:
			return VX_TYPE_UINT16;
		case CV_16SC1:
			return VX_TYPE_INT16;
		case CV_32SC1:
			return VX_TYPE_INT32;
		case CV_32FC1:
			return VX_TYPE_FLOAT32;
		case CV_64FC1:
			return VX_TYPE_FLOAT64;
		case CV_32FC2:
			return NVX_TYPE_POINT2F;
		case CV_32FC3:
			return NVX_TYPE_POINT3F;
		}
		CV_Error(CV_StsUnsupportedFormat, "Unsupported format");
		return 0;
	}

	/**
	* \ingroup nvx_opencv_interop
	* \brief Converts from OpenVX Image's format to OpenCV Mat's type.
	*
	* \param [in] format       OpenVX Image's format.
	* \param [in] plane_index  Optional OpenVX Image's plane index.
	*
	* \return OpenCV Mat's type.
	*/
	inline int convertVXImageFormatToCVMatType(vx_df_image format, vx_uint32 plane_index = 0)
	{
		switch (format)
		{
		case VX_DF_IMAGE_U8:
		case VX_DF_IMAGE_YUV4:
		case VX_DF_IMAGE_IYUV:
			return CV_8UC1;
		case VX_DF_IMAGE_U16:
			return CV_16UC1;
		case VX_DF_IMAGE_S16:
			return CV_16SC1;
		case VX_DF_IMAGE_U32:
		case VX_DF_IMAGE_S32:
			return CV_32SC1;
		case NVX_DF_IMAGE_F32:
			return CV_32FC1;
		case NVX_DF_IMAGE_2F32:
			return CV_32FC2;
		case NVX_DF_IMAGE_2S16:
			return CV_16SC2;
		case VX_DF_IMAGE_UYVY:
		case VX_DF_IMAGE_YUYV:
			return CV_8UC2;
		case VX_DF_IMAGE_RGB:
			return CV_8UC3;
		case NVX_DF_IMAGE_RGB16:
			return CV_16SC3;
		case VX_DF_IMAGE_RGBX:
			return CV_8UC4;
		case VX_DF_IMAGE_NV12:
		case VX_DF_IMAGE_NV21:
			return plane_index == 0 ? CV_8UC1 : CV_8UC2;
		}
		CV_Error(CV_StsUnsupportedFormat, "Unsupported format");
		return 0;
	}

	/**
	* \ingroup nvx_opencv_interop
	* \brief Converts from OpenCV Mat's type to OpenVX Image's format.
	*
	* \param [in] mat_type     OpenCV Mat's type.
	*
	* \return OpenVX Image's format.
	*/
	inline vx_df_image convertCVMatTypeToVXImageFormat(int mat_type)
	{
		switch (mat_type)
		{
		case CV_8UC1:
			return VX_DF_IMAGE_U8;
		case CV_16UC1:
			return VX_DF_IMAGE_U16;
		case CV_16SC1:
			return VX_DF_IMAGE_S16;
		case CV_32SC1:
			return VX_DF_IMAGE_S32;
		case CV_32FC1:
			return NVX_DF_IMAGE_F32;
		case CV_32FC2:
			return NVX_DF_IMAGE_2F32;
		case CV_16SC2:
			return NVX_DF_IMAGE_2S16;
		case CV_8UC3:
			return VX_DF_IMAGE_RGB;
		case CV_8UC4:
			return VX_DF_IMAGE_RGBX;
		case CV_16SC3:
			return NVX_DF_IMAGE_RGB16;
		}
		CV_Error(CV_StsUnsupportedFormat, "Unsupported format");
		return 0;
	}

	/**
	* \ingroup nvx_opencv_interop
	* \brief Copies data from OpenVX Matrix to OpenCV Mat.
	*
	* \param [in]  src_mat     Input OpenVX Matrix.
	* \param [out] dst_mat     Output OpenCV Mat.
	*/
	inline void copyVXMatrixToCVMat(vx_matrix src_mat, cv::Mat& dst_mat)
	{
		vx_status status = VX_SUCCESS;
		vx_size rows_num = 0, cols_num = 0;
		vx_enum elem_type = 0;

		status = vxQueryMatrix(src_mat, VX_MATRIX_ATTRIBUTE_TYPE, &elem_type, sizeof(elem_type));
		CV_Assert(status == VX_SUCCESS);

		status = vxQueryMatrix(src_mat, VX_MATRIX_ATTRIBUTE_ROWS, &rows_num, sizeof(rows_num));
		CV_Assert(status == VX_SUCCESS);
		CV_Assert(rows_num <= static_cast<vx_size>(std::numeric_limits<int>::max()));

		status = vxQueryMatrix(src_mat, VX_MATRIX_ATTRIBUTE_COLUMNS, &cols_num, sizeof(cols_num));
		CV_Assert(status == VX_SUCCESS);
		CV_Assert(cols_num <= static_cast<vx_size>(std::numeric_limits<int>::max()));

		dst_mat.create(static_cast<int>(rows_num), static_cast<int>(cols_num), convertVXMatrixTypeToCVMatType(elem_type));
		CV_Assert(dst_mat.isContinuous());

		status = vxReadMatrix(src_mat, dst_mat.data);
		CV_Assert(status == VX_SUCCESS);
	}

	/**
	* \ingroup nvx_opencv_interop
	* \brief Copies data from OpenCV Mat to OpenVX Matrix.
	*
	* \param [in]  src_mat     Input OpenCV Mat. It must be a continuous matrix.
	* \param [out] dst_mat     Output OpenVX Matrix.
	*/
	inline void copyCVMatToVXMatrix(const cv::Mat& src_mat, vx_matrix dst_mat)
	{
		vx_status status = VX_SUCCESS;
		vx_size dst_rows_num = 0, dst_cols_num = 0;
		vx_enum dst_elem_type = 0;

		status = vxQueryMatrix(dst_mat, VX_MATRIX_ATTRIBUTE_TYPE, &dst_elem_type, sizeof(dst_elem_type));
		CV_Assert(status == VX_SUCCESS);

		status = vxQueryMatrix(dst_mat, VX_MATRIX_ATTRIBUTE_ROWS, &dst_rows_num, sizeof(dst_rows_num));
		CV_Assert(status == VX_SUCCESS);

		status = vxQueryMatrix(dst_mat, VX_MATRIX_ATTRIBUTE_COLUMNS, &dst_cols_num, sizeof(dst_cols_num));
		CV_Assert(status == VX_SUCCESS);

		CV_Assert(src_mat.isContinuous());
		CV_Assert(static_cast<vx_size>(src_mat.cols) == dst_cols_num && static_cast<vx_size>(src_mat.rows) == dst_rows_num);
		CV_Assert(src_mat.type() == convertVXMatrixTypeToCVMatType(dst_elem_type));

		status = vxWriteMatrix(dst_mat, src_mat.data);
		CV_Assert(status == VX_SUCCESS);
	}

	/**
	* \ingroup nvx_opencv_interop
	* \brief Creates OpenVX Matrix object and copies data from OpenCV Mat.
	*
	* \param [in] context      OpenVX context.
	* \param [in] src_mat      Input OpenCV Mat.
	*
	* \return OpenVX Matrix.
	*/
	inline vx_matrix cloneCVMatToVXMatrix(vx_context context, const cv::Mat& src_mat)
	{
		vx_matrix res_matrix = vxCreateMatrix(context, convertCVMatTypeToVXMatrixType(src_mat.type()),
			src_mat.cols, src_mat.rows);
		CV_Assert(vxGetStatus((vx_reference)res_matrix) == VX_SUCCESS);

		copyCVMatToVXMatrix(src_mat, res_matrix);

		return res_matrix;
	}

	/**
	* \ingroup nvx_opencv_interop
	* \brief Creates OpenVX Image from OpenCV Mat without data copy.
	*
	* The OpenVX Image points to the same pixels as the OpenCV Mat.
	*
	* \note The OpenCV Mat object must not be released until the OpenVX Image object is destroyed.
	*
	* \param [in] context      OpenVX context.
	* \param [in] mat          Input OpenCV Mat to import.
	*
	* \return OpenVX Image object imported from input OpenCV Mat.
	*/
	inline vx_image createVXImageFromCVMat(vx_context context, const cv::Mat& mat)
	{
		vx_df_image format = convertCVMatTypeToVXImageFormat(mat.type());

		vx_imagepatch_addressing_t addrs[1];
		addrs[0].dim_x = mat.cols;
		addrs[0].dim_y = mat.rows;
		addrs[0].stride_x = static_cast<vx_int32>(mat.elemSize());
		addrs[0].stride_y = static_cast<vx_int32>(mat.step);

		void *ptrs[1] = { const_cast<uchar *>(mat.ptr()) };

		vx_image img = vxCreateImageFromHandle(context, format, addrs, ptrs, VX_IMPORT_TYPE_HOST);
		CV_Assert(vxGetStatus((vx_reference)img) == VX_SUCCESS);

		return img;
	}

	/**
	* \ingroup nvx_opencv_interop
	* \brief Creates OpenVX Image from OpenCV GpuMat without data copy.
	*
	* The OpenVX Image points to the same pixels as the OpenCV GpuMat.
	*
	* \note The OpenCV GpuMat object must not be released until the OpenVX Image object is destroyed.
	*
	* \param [in] context      OpenVX context.
	* \param [in] mat          Input OpenCV GpuMat to import.
	*
	* \return OpenVX Image object imported from input OpenCV GpuMat.
	*/
	inline vx_image createVXImageFromCVGpuMat(vx_context context, const cv::cuda::GpuMat& mat)
	{
		vx_df_image format = convertCVMatTypeToVXImageFormat(mat.type());

		vx_imagepatch_addressing_t addrs[1];
		addrs[0].dim_x = mat.cols;
		addrs[0].dim_y = mat.rows;
		addrs[0].stride_x = static_cast<vx_int32>(mat.elemSize());
		addrs[0].stride_y = static_cast<vx_int32>(mat.step);

		void *ptrs[1] = { const_cast<uchar *>(mat.ptr()) };

		vx_image img = vxCreateImageFromHandle(context, format, addrs, ptrs, NVX_IMPORT_TYPE_CUDA);
		CV_Assert(vxGetStatus((vx_reference)img) == VX_SUCCESS);

		return img;
	}

	/**
	* \ingroup nvx_opencv_interop
	* \brief Utility class to map OpenVX Image into OpenCV Mat or GpuMat.
	*
	* The class maps OpenVX Image into OpenCV Mat or GpuMat in constructor and
	* unmaps OpenVX Image in destructor.
	*
	* \note The input OpenVX Image must not be destroyed until the class' destructor is called.
	*/
	class VXImageToCVMatMapper
	{
	public:
		/**
		* \brief Maps input OpenVX Image into OpenCV Mat or GpuMat without memory copy.
		*
		* \param [in] image            Input OpenVX Image.
		* \param [in] plane_index      Plane index to map.
		* \param [in] rect             Region to map. Use `NULL` to map the whole Image region.
		* \param [in] usage            Intended usage of mapped memory
		*                                  (`VX_READ_ONLY`, `VX_WRITE_ONLY` or `VX_READ_AND_WRITE`).
		* \param [in] memory_type      Intended memory type of the mapped memory
		*                                  (`VX_IMPORT_TYPE_HOST` for Mat or `NVX_IMPORT_TYPE_CUDA` for GpuMat).
		*/
		explicit VXImageToCVMatMapper(vx_image image,
			vx_uint32 plane_index = 0,
			const vx_rectangle_t *rect = nullptr,
			vx_enum usage = VX_READ_AND_WRITE,
			vx_enum memory_type = VX_IMPORT_TYPE_HOST) :
			image_(image), plane_index_(plane_index), memory_type_(memory_type), ptr_(nullptr)
		{
			vx_status status = VX_SUCCESS;

			if (rect)
			{
				rect_.start_x = rect->start_x;
				rect_.start_y = rect->start_y;
				rect_.end_x = rect->end_x;
				rect_.end_y = rect->end_y;
			}
			else
			{
				rect_.start_x = rect_.start_y = 0;

				status = vxQueryImage(image_, VX_IMAGE_ATTRIBUTE_WIDTH, &rect_.end_x, sizeof(rect_.end_x));
				CV_Assert(status == VX_SUCCESS);

				status = vxQueryImage(image_, VX_IMAGE_ATTRIBUTE_HEIGHT, &rect_.end_y, sizeof(rect_.end_y));
				CV_Assert(status == VX_SUCCESS);
			}

			vx_df_image format = VX_DF_IMAGE_VIRT;
			status = vxQueryImage(image_, VX_IMAGE_ATTRIBUTE_FORMAT, &format, sizeof(format));
			CV_Assert(status == VX_SUCCESS);

			int type = convertVXImageFormatToCVMatType(format, plane_index_);

			status = nvxMapImagePatch(image_, &rect_, plane_index_, &addr_, &ptr_, usage, memory_type_, NVX_MAP_NO_PIXEL_GAPS);
			CV_Assert(status == VX_SUCCESS);

			int cols = addr_.dim_x * addr_.scale_x / VX_SCALE_UNITY;
			int rows = addr_.dim_y * addr_.scale_y / VX_SCALE_UNITY;
			int step = addr_.stride_y;

			if (memory_type_ == VX_IMPORT_TYPE_HOST)
			{
				cv_mat_ = cv::Mat(rows, cols, type, ptr_, step);
			}
			else if (memory_type_ == NVX_IMPORT_TYPE_CUDA)
			{
				cv_gpumat_ = cv::cuda::GpuMat(rows, cols, type, ptr_, step);
			}
		}

		/**
		* \brief Unmaps a mapped region of an OpenVX Image.
		*/
		~VXImageToCVMatMapper()
		{
			nvxUnmapImagePatch(image_, &rect_, plane_index_, ptr_, memory_type_);
		}

		/**
		* \brief Gets mapped OpenCV Mat.
		*
		* \return Mapped OpenCV Mat.
		*/
		cv::Mat getMat()
		{
			CV_Assert(!cv_mat_.empty());
			return cv_mat_;
		}

		/**
		* \brief Gets mapped OpenCV GpuMat.
		*
		* \return Mapped OpenCV GpuMat.
		*/
		cv::cuda::GpuMat getGpuMat()
		{
			CV_Assert(!cv_gpumat_.empty());
			return cv_gpumat_;
		}

	private:
		vx_image image_;
		vx_uint32 plane_index_;
		vx_enum memory_type_;

		vx_rectangle_t rect_;
		vx_imagepatch_addressing_t addr_;
		void* ptr_;

		cv::Mat cv_mat_;
		cv::cuda::GpuMat cv_gpumat_;
	};
}

#else // VISIONWORKS_7_5

namespace nvx_cv {

	inline int convertVXMatrixTypeToCVMatType(vx_enum matrix_type)
	{
		switch (matrix_type)
		{
		case VX_TYPE_UINT8:
			return CV_8UC1;
		case VX_TYPE_INT8:
			return CV_8SC1;
		case VX_TYPE_UINT16:
			return CV_16UC1;
		case VX_TYPE_INT16:
			return CV_16SC1;
		case VX_TYPE_UINT32:
		case VX_TYPE_INT32:
			return CV_32SC1;
		case VX_TYPE_FLOAT32:
			return CV_32FC1;
		case VX_TYPE_FLOAT64:
			return CV_64FC1;
		}
		CV_Error(CV_StsUnsupportedFormat, "Unsupported format");
		return 0;
	}

	inline vx_enum convertCVMatTypeToVXMatrixType(int mat_type)
	{
		switch (mat_type)
		{
		case CV_8UC1:
			return VX_TYPE_UINT8;
		case CV_8SC1:
			return VX_TYPE_INT8;
		case CV_16UC1:
			return VX_TYPE_UINT16;
		case CV_16SC1:
			return VX_TYPE_INT16;
		case CV_32SC1:
			return VX_TYPE_INT32;
		case CV_32FC1:
			return VX_TYPE_FLOAT32;
		case CV_64FC1:
			return VX_TYPE_FLOAT64;
		}
		CV_Error(CV_StsUnsupportedFormat, "Unsupported format");
		return 0;
	}

	/**
	* \ingroup nvx_opencv_interop
	* \brief Converts from OpenVX Image's format to OpenCV Mat's type.
	*
	* \param [in] format       OpenVX Image's format.
	* \param [in] plane_index  Optional OpenVX Image's plane index.
	*
	* \return OpenCV Mat's type.
	*/
	inline int convertVXImageFormatToCVMatType(vx_df_image format, vx_uint32 plane_index = 0)
	{
		switch (format)
		{
		case VX_DF_IMAGE_U8:
		case VX_DF_IMAGE_YUV4:
		case VX_DF_IMAGE_IYUV:
			return CV_8UC1;
		case VX_DF_IMAGE_U16:
			return CV_16UC1;
		case VX_DF_IMAGE_S16:
			return CV_16SC1;
		case VX_DF_IMAGE_U32:
		case VX_DF_IMAGE_S32:
			return CV_32SC1;
		case NVX_DF_IMAGE_F32:
			return CV_32FC1;
		case VX_DF_IMAGE_UYVY:
		case VX_DF_IMAGE_YUYV:
			return CV_8UC2;
		case VX_DF_IMAGE_RGB:
			return CV_8UC3;
		case VX_DF_IMAGE_RGBX:
			return CV_8UC4;
		case VX_DF_IMAGE_NV12:
		case VX_DF_IMAGE_NV21:
			return plane_index == 0 ? CV_8UC1 : CV_8UC2;
		}
		CV_Error(CV_StsUnsupportedFormat, "Unsupported format");
		return 0;
	}

	inline vx_df_image convertCVMatTypeToVXImageFormat(int mat_type)
	{
		switch (mat_type)
		{
		case CV_8UC1:
			return VX_DF_IMAGE_U8;
		case CV_16SC1:
			return VX_DF_IMAGE_S16;
		case CV_32FC1:
			return NVX_DF_IMAGE_F32;
		case CV_8UC3:
			return VX_DF_IMAGE_RGB;
		case CV_8UC4:
			return VX_DF_IMAGE_RGBX;
		}
		CV_Error(CV_StsUnsupportedFormat, "Unsupported format");
		return 0;
	}

	inline void copyVXMatrixToCVMat(vx_matrix src_mat, cv::Mat & dst_mat)
	{
		vx_status status = VX_SUCCESS;
		vx_size rows_num = 0, cols_num = 0;
		vx_enum elem_type = 0;

		status = vxQueryMatrix(src_mat, VX_MATRIX_ATTRIBUTE_TYPE, &elem_type, sizeof(elem_type));
		CV_Assert(status == VX_SUCCESS);

		status = vxQueryMatrix(src_mat, VX_MATRIX_ATTRIBUTE_ROWS, &rows_num, sizeof(rows_num));
		CV_Assert(status == VX_SUCCESS);
		CV_Assert(rows_num <= static_cast<vx_size>(std::numeric_limits<int>::max()));

		status = vxQueryMatrix(src_mat, VX_MATRIX_ATTRIBUTE_COLUMNS, &cols_num, sizeof(cols_num));
		CV_Assert(status == VX_SUCCESS);
		CV_Assert(cols_num <= static_cast<vx_size>(std::numeric_limits<int>::max()));

		dst_mat.create(int(rows_num), int(cols_num), convertVXMatrixTypeToCVMatType(elem_type));

		status = vxReadMatrix(src_mat, dst_mat.data);
		CV_Assert(status == VX_SUCCESS);
	}

	inline void copyCVMatToVXMatrix(const cv::Mat & src_mat, vx_matrix dst_mat)
	{
		vx_status status = VX_SUCCESS;
		vx_size dst_rows_num = 0, dst_cols_num = 0;
		vx_enum dst_elem_type = 0;

		status = vxQueryMatrix(dst_mat, VX_MATRIX_ATTRIBUTE_TYPE, &dst_elem_type, sizeof(dst_elem_type));
		CV_Assert(status == VX_SUCCESS);

		status = vxQueryMatrix(dst_mat, VX_MATRIX_ATTRIBUTE_ROWS, &dst_rows_num, sizeof(dst_rows_num));
		CV_Assert(status == VX_SUCCESS);

		status = vxQueryMatrix(dst_mat, VX_MATRIX_ATTRIBUTE_COLUMNS, &dst_cols_num, sizeof(dst_cols_num));
		CV_Assert(status == VX_SUCCESS);

		CV_Assert(src_mat.isContinuous());
		CV_Assert(((vx_size)src_mat.cols) == dst_cols_num && ((vx_size)src_mat.rows) == dst_rows_num);
		CV_Assert(src_mat.type() == convertVXMatrixTypeToCVMatType(dst_elem_type));

		status = vxWriteMatrix(dst_mat, src_mat.data);
		CV_Assert(status == VX_SUCCESS);
	}

	inline vx_matrix cloneCVMatToVXMatrix(vx_context context, const cv::Mat & src_mat)
	{
		vx_matrix res_matrix = vxCreateMatrix(context, convertCVMatTypeToVXMatrixType(src_mat.type()),
			src_mat.cols, src_mat.rows);
		CV_Assert(vxGetStatus((vx_reference)res_matrix) == VX_SUCCESS);
		copyCVMatToVXMatrix(src_mat, res_matrix);

		return res_matrix;
	}

	// vx_image will be pointing to the same pixels as the cv::Mat
	inline vx_image createVXImageFromCVMat(vx_context context, const cv::Mat & mat)
	{
		vx_imagepatch_addressing_t patch = { (vx_uint32)mat.cols, (vx_uint32)mat.rows,
			(vx_int32)mat.elemSize(), (vx_int32)mat.step,
			VX_SCALE_UNITY, VX_SCALE_UNITY,
			1u, 1u };
		void *ptr = (void*)mat.ptr();
		vx_df_image format = convertCVMatTypeToVXImageFormat(mat.type());
		return vxCreateImageFromHandle(context, format, &patch, (void **)&ptr, VX_IMPORT_TYPE_HOST);
	}

	// vx_image will be pointing to the same pixels as the cv::GpuMat
	inline vx_image createVXImageFromCVGpuMat(vx_context context, const cv::cuda::GpuMat & mat)
	{
		vx_imagepatch_addressing_t patch = { (vx_uint32)mat.cols, (vx_uint32)mat.rows,
			(vx_int32)mat.elemSize(), (vx_int32)mat.step,
			VX_SCALE_UNITY, VX_SCALE_UNITY,
			1u, 1u };
		void *ptr = (void*)mat.ptr();
		vx_df_image format = convertCVMatTypeToVXImageFormat(mat.type());
		return vxCreateImageFromHandle(context, format, &patch, (void **)&ptr, NVX_IMPORT_TYPE_CUDA);
	}

	class VXImageToCVMatMapper
	{
	public:
		explicit VXImageToCVMatMapper(vx_image image,
			vx_uint32 plane_index = 0,
			const vx_rectangle_t *rect = NULL,
			vx_enum usage = VX_READ_AND_WRITE,
			vx_enum memory_type = 57345) :
			image_(image), plane_index_(plane_index), m_memory_type(memory_type)
		{
			vx_status status = VX_SUCCESS;

			if (rect)
			{
				rect_.start_x = rect->start_x;
				rect_.start_y = rect->start_y;
				rect_.end_x = rect->end_x;
				rect_.end_y = rect->end_y;
			}
			else
			{
				rect_.start_x = rect_.start_y = 0;

				status = vxQueryImage(image_, VX_IMAGE_ATTRIBUTE_WIDTH, &rect_.end_x, sizeof(rect_.end_x));
				CV_Assert(status == VX_SUCCESS);

				status = vxQueryImage(image_, VX_IMAGE_ATTRIBUTE_HEIGHT, &rect_.end_y, sizeof(rect_.end_y));
				CV_Assert(status == VX_SUCCESS);
			}

			vx_df_image format = VX_DF_IMAGE_VIRT;
			status = vxQueryImage(image_, VX_IMAGE_ATTRIBUTE_FORMAT, &format, sizeof(format));
			CV_Assert(status == VX_SUCCESS);

			int type = 0;
			switch (format)
			{
			case VX_DF_IMAGE_U8:
			case VX_DF_IMAGE_YUV4:
			case VX_DF_IMAGE_IYUV:
				type = CV_8UC1;
				break;
			case VX_DF_IMAGE_U16:
				type = CV_16UC1;
				break;
			case VX_DF_IMAGE_S16:
				type = CV_16SC1;
				break;
			case VX_DF_IMAGE_U32:
			case VX_DF_IMAGE_S32:
				type = CV_32SC1;
				break;
			case NVX_DF_IMAGE_F32:
				type = CV_32FC1;
				break;
			case NVX_DF_IMAGE_2F32:
				type = CV_32FC2;
				break;
			case VX_DF_IMAGE_UYVY:
			case VX_DF_IMAGE_YUYV:
				type = CV_8UC2;
				break;
			case VX_DF_IMAGE_RGB:
				type = CV_8UC3;
				break;
			case NVX_DF_IMAGE_RGB16:
				type = CV_16SC3;
				break;
			case VX_DF_IMAGE_RGBX:
				type = CV_8UC4;
				break;
			case VX_DF_IMAGE_NV12:
			case VX_DF_IMAGE_NV21:
				type = plane_index_ == 0 ? CV_8U : CV_8UC2;
				break;
			default:
				CV_Error(CV_StsUnsupportedFormat, "Unsupported format");
			}

			void* ptr = NULL;
			status = vxAccessImagePatch(image_, &rect_, plane_index_, &addr_, &ptr, usage);
			CV_Assert(status == VX_SUCCESS);
			CV_Assert(ptr != NULL);

			int cols = addr_.dim_x * addr_.scale_x / VX_SCALE_UNITY;
			int rows = addr_.dim_y * addr_.scale_y / VX_SCALE_UNITY;
			int step = addr_.stride_y;

			cv_mat_ = cv::Mat(rows, cols, type, ptr, step);
		}

		~VXImageToCVMatMapper()
		{
			if (!cv_mat_.empty())
			{
				vxCommitImagePatch(image_, &rect_, plane_index_, &addr_, cv_mat_.data);
			}
		}

		cv::Mat& getMat()
		{
			return cv_mat_;
		}

	private:
		vx_image image_;
		vx_uint32 plane_index_;

		vx_rectangle_t rect_;
		vx_imagepatch_addressing_t addr_;

		cv::Mat cv_mat_;

		vx_enum m_memory_type;
	};
}

#endif // VISIONWORKS_7_5

#endif // !__NVX_OPENCV_INTEROP_HPP__
