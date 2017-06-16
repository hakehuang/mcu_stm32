require 'find'
require 'fileutils'
require 'json'
require "awesome_print"
require 'yaml'
require 'tempfile'
require 'pathname'
require 'tenjin'
require 'optparse'
require 'ostruct'


class Parser
  def self.parse(options)
    @args = OpenStruct.new
    @args.tf = "template.yml"
    @args.cf = "chip.yml"
    @args.of = "."

    opt_parser = OptionParser.new do |opts|
      opts.banner = "Usage: gen_component.rb [options]"

      opts.on("-ttemplate", "--tf=template", "template file") do |n|
        @args.tf = n
      end

      opts.on("-cdriverlist", "--cf=drivers", "drivers list file") do |n|
        @args.cf = n
      end

      opts.on("-ooutput", "--of=out", "output path") do |n|
        @args.of = n
      end
 
      opts.on("-h", "--help", "Prints this help") do
        puts opts
        exit
      end
    end

    opt_parser.parse!(options)
    return @args.to_h
  end
end


engine = Tenjin::Engine.new()


if ARGV[0] == "help" || ARGV[0] == "-h"
	Parser.parse(["-h"])
	exit
end

@command_lines = Marshal.load(Marshal.dump(Parser.parse(ARGV)))

ap @command_lines

@comp_list = Array.new



content = File::read(@command_lines[:cf].gsub("\\","/"))
content = YAML::load(content)
content.each_key do |comp|
    @comp_list.insert(-1, comp)
end


@comp_list.each do |comp|
  puts "processing #{comp}"
  context = {
    :COMP => comp
  }

  output = engine.render(@command_lines[:tf], context)
  next if output.nil?
  output_format = YAML.load(output)
  FileUtils::mkdir_p @command_lines[:of]
  File.open(File.join(@command_lines[:of],"#{comp}.yml"), 'w') {|f| f.write(YAML.dump(output_format)) }
end
