#! ruby -I../

require 'yaml'
require 'yml_merger'

require 'awesome_print'
require 'ebngen'
require 'logger'

@logger = Logger.new(STDOUT)
@logger.level = Logger::DEBUG

@entry_yml = "projects/st/stm32f03_evk.yml"
@search_path  = (Pathname.new(File.dirname(__FILE__)).realpath + 'records/').to_s
merge_unit      = YML_Merger.new(
    @entry_yml, @search_path, logger: @logger
)
merged_data     = merge_unit.process()
#File.write('./merged_data.yml', YAML.dump(merged_data))

translator_unit = Translator.new(
    merged_data, logger: Logger.new(STDOUT)
)
translated_data = translator_unit.translate()

File.write('./unified_data.yml', YAML.dump(translated_data[0]))

translated_data[0].each_key do |project|
  options = {
    "paths" => {
     "default_path" => Dir.pwd,
     "output_root" => Dir.pwd + '/../build',
     "stm32_sdk_path"  => Dir.pwd + '/../',
  	#'mqx_path' => @mqx_path,
     "app_path" => Dir.pwd + '/../'
    },
    "all" => translated_data[0][project]
  }
  mygenerator = Generator.new(options)
  mygenerator.generate_project_set('iar',translated_data[0][project])
  mygenerator.generate_projects('iar', '', translated_data[0][project])
end
#mygenerator.generate_projects('cmake', '', translated_data[0]['hello_world'])