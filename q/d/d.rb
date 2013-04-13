#!/usr/bin/env ruby

require 'pp'

def rec(okeys, akeys, ikeys, opened)
  if okeys.size == opened.size
    #pp opened
    opened
  else
    r = nil
    okeys.each_with_index do |o, i|
      next if opened.include?(i)
      j = ikeys.index(o)
      next if j.nil?
      ikeys2 = ikeys.dup
      ikeys2.delete_at(j)
      s = rec(okeys, akeys, ikeys2+akeys[i], opened+[i])
      next if s.nil?
      r = s if r.nil? || (s <=> r) < 0
    end
    r
  end
end

t = gets.to_i

t.times do |i|
  k, n = gets.chomp.split.map(&:to_i)
  ikeys = gets.chomp.split.map(&:to_i)
  okeys = []
  akeys = []
  n.times do
    ak = gets.chomp.split.map(&:to_i)
    okeys << ak.shift
    ak.shift
    akeys << ak
  end
  pp [okeys, akeys, ikeys]
  r = rec(okeys, akeys, ikeys, [])
  puts "Case ##{i+1}: #{r ? r.map(&:next).join(" ") : "IMPOSSIBLE"}"
end
