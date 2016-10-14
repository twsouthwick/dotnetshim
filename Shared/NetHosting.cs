using System;
using System.Runtime.InteropServices;

namespace Demo
{
    public sealed class DotNetHost : IDisposable
    {
        const string Dll = @"dotnetshim.dll";

        private IntPtr _ptr;

        public DotNetHost(string runtime)
        {
            _ptr = Create(runtime);

            try
            {
                Marshal.ThrowExceptionForHR(GetStatus(_ptr));
            }
            catch(COMException)
            {
                Delete(ref _ptr);
                throw;
            }
        }

        public int Run(string path, string typename, string method)
        {
            int result = 0;
            var hr = RunMethod(_ptr, ref result, path, typename, method);

            Marshal.ThrowExceptionForHR(hr);

            return result;
        }

        [DllImport(Dll, CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetStatus(IntPtr shim);

        [DllImport(Dll, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        private static extern IntPtr Create(
            [MarshalAs(UnmanagedType.LPWStr)]
                string runtimeVersion);

        [DllImport(Dll, CallingConvention = CallingConvention.Cdecl)]
        private static extern int Delete(ref IntPtr ptr);

        [DllImport(Dll, CallingConvention = CallingConvention.Cdecl)]
        private static extern int RunMethod(IntPtr ptr, ref int result,
            [MarshalAs(UnmanagedType.LPWStr)]
                string path,
            [MarshalAs(UnmanagedType.LPWStr)]
                string typename,
            [MarshalAs(UnmanagedType.LPWStr)]
                string method);

        public void Dispose()
        {
            var hr = Delete(ref _ptr);

            Marshal.ThrowExceptionForHR(hr);
        }
    }
}
