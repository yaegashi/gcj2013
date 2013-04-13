#!/usr/bin/env ruby

require 'pp'

def scan(n, m, field)

  n.times do |r|
    m.times do |c|
      h = field[r][c]
      rmax = field[r].max
      cmax = field.map{|i| i[c]}.max
      return "NO" if h < rmax && h < cmax
    end
  end

  return "YES"

end

t = gets.to_i

t.times do |i|
  n, m = gets.chomp.split.map(&:to_i)
  field = []
  n.times do
    field << gets.chomp.split.map(&:to_i)
  end
  puts "Case ##{i+1}: #{scan(n, m, field)}"
end
