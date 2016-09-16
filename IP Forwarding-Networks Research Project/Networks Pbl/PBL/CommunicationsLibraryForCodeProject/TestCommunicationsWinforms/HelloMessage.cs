using System;
using System.Threading;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using BrainTechLLC.EmlenMud.Interfaces;
using BrainTechLLC.ThreadSafeObjects;
using BrainTechLLC.EmlenMud.Communication;

namespace BrainTechLLC
{	
	/// <summary>
	/// A simple hello message to demonstrate how to transmit objects to/from client and server
	/// </summary>
	[Serializable]
	public class HelloMessage
	{
		public string Message { get; set; }

		public HelloMessage() { }
		public HelloMessage(string message) { Message = message; }
	}
}


