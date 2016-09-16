using System;
using System.Threading;
using System.ComponentModel;
using System.Collections.Generic;
using BrainTechLLC.ThreadSafeObjects;
using Hyper.ComponentModel;

namespace BrainTechLLC.ThreadSafeObjects
{		
	public interface IKeyedOnProperty<T>
	{
		T Key { get; }
	}
}
