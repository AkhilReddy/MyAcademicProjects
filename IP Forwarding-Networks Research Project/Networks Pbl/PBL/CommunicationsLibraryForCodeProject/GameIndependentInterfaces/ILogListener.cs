//using System;
//using System.ComponentModel;

//namespace BrainTechLLC.EmlenMud.Interfaces
//{
//    public class SimpleEventArgs<T> : EventArgs
//    {
//        public T Value { get; set; }
//        public SimpleEventArgs(T val) { Value = val; }
//        public SimpleEventArgs() { }
//    }

//    public interface ILogListener
//    {
//        event EventHandler<SimpleEventArgs<string>> NewLogEntry;
//        void OnNewLogEntry(SimpleEventArgs<string> eventArgs);
//        bool IsListening { get; set; }
//    }
//}
