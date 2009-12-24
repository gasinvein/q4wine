<?php

/***************************************************************************
 *   Copyright (C) 2009,2010 by Malakhov Alexey                            *
 *   brezerk@gmail.com                                                     *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 ***************************************************************************/

require_once("./cfg/config.inc");

Class MemChace { 
	
	private $memcache_timeout;
	private $memcache;

   function __construct(){
		/* MemChace class constructor */

		// Get config values from ./cfg/config.inc
		global $memcache_host;
		global $memcache_port;
		global $memcache_timeout;
		
		$this->memcache_timeout=$memcache_timeout;
				  
		$this->memcache = new Memcache;
		$this->memcache->connect($memcache_host, $memcache_port) or die ("Could not connect to memchace service");
   }
   
   function setCache($object, $key){
		if (!$object)
			return;
			
		if (!$key)
			return;
		
		$this->memcache->set($key, $object, flase, $this->memcache_timeout);
	}
	
	function getCache($key){
		return $this->memcache->get($key);
	}
};

?>
 