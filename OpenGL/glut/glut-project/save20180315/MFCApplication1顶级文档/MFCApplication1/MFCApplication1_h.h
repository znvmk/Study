

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Tue Mar 13 19:29:32 2018
 */
/* Compiler settings for MFCApplication1.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __MFCApplication1_h_h__
#define __MFCApplication1_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMFCApplication1_FWD_DEFINED__
#define __IMFCApplication1_FWD_DEFINED__
typedef interface IMFCApplication1 IMFCApplication1;

#endif 	/* __IMFCApplication1_FWD_DEFINED__ */


#ifndef __CMFCApplication1Doc_FWD_DEFINED__
#define __CMFCApplication1Doc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMFCApplication1Doc CMFCApplication1Doc;
#else
typedef struct CMFCApplication1Doc CMFCApplication1Doc;
#endif /* __cplusplus */

#endif 	/* __CMFCApplication1Doc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MFCApplication1_LIBRARY_DEFINED__
#define __MFCApplication1_LIBRARY_DEFINED__

/* library MFCApplication1 */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MFCApplication1;

#ifndef __IMFCApplication1_DISPINTERFACE_DEFINED__
#define __IMFCApplication1_DISPINTERFACE_DEFINED__

/* dispinterface IMFCApplication1 */
/* [uuid] */ 


EXTERN_C const IID DIID_IMFCApplication1;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("7FA80ABE-4544-40C0-A9F2-46BF301D4CA0")
    IMFCApplication1 : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMFCApplication1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMFCApplication1 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMFCApplication1 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMFCApplication1 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMFCApplication1 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMFCApplication1 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMFCApplication1 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMFCApplication1 * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IMFCApplication1Vtbl;

    interface IMFCApplication1
    {
        CONST_VTBL struct IMFCApplication1Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMFCApplication1_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMFCApplication1_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMFCApplication1_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMFCApplication1_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMFCApplication1_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMFCApplication1_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMFCApplication1_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMFCApplication1_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CMFCApplication1Doc;

#ifdef __cplusplus

class DECLSPEC_UUID("48BB0B3D-D0F3-4451-9CEA-44511B4AA8EA")
CMFCApplication1Doc;
#endif
#endif /* __MFCApplication1_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


